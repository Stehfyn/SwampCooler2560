#include "SwampCooler2560.h"
#include "states/State.h"
#include "states/Idle.h"
#include "states/Disabled.h"

SwampCooler2560PinMap::SwampCooler2560PinMap(

    const uint8_t _power_switch,
    
    const uint8_t _joystick_Rx,
    const uint8_t _joystick_Ry,
    
    const uint8_t _led_yellow,
    const uint8_t _led_green,
    const uint8_t _led_blue,
    const uint8_t _led_red,
    
    const uint8_t _lcd_rs,
    const uint8_t _lcd_en,
    const uint8_t _lcd_d4,
    const uint8_t _lcd_d5,
    const uint8_t _lcd_d6,
    const uint8_t _lcd_d7,
    
    const uint8_t _dht11,
    const uint8_t _water_sensor,
    
    const uint8_t _rtcSDA,
    const uint8_t _rtcSCL,
    
    const uint8_t _fan_motor,
    const uint8_t _vent_servo ) :

        power_switch( _power_switch ),

        joystick_Rx ( _joystick_Rx ),
        joystick_Ry ( _joystick_Ry ),

        led_yellow  ( _led_yellow ),
        led_green   ( _led_green ),
        led_blue    ( _led_blue ),
        led_red     ( _led_red ),

        lcd_rs      ( _lcd_rs ),
        lcd_en      ( _lcd_en ),
        lcd_d4      ( _lcd_d4 ),
        lcd_d5      ( _lcd_d5 ),
        lcd_d6      ( _lcd_d6 ),
        lcd_d7      ( _lcd_d7 ),

        rtcSDA      ( _rtcSDA ),
        rtcSCL      ( _rtcSCL ),

        dht11       ( _dht11 ),
        fan_motor   ( _fan_motor ),
        vent_servo  ( _vent_servo ),
        water_sensor( _water_sensor ),

        m_valid     ( true )
{
    /// No identical pins == a valid PinMap
    uint8_t pins[] = {
        power_switch,
        joystick_Rx, joystick_Ry,
        led_yellow, led_green, led_blue, led_red,
        lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7,
        dht11,
        water_sensor,
        rtcSDA, rtcSCL,
        fan_motor,
        vent_servo };

    for (uint8_t i = 0; i < sizeof(pins) - 1; i++)
    {
        for (uint8_t j = i + 1; j < sizeof(pins); j++ )
        {
            if (pins[i] == pins[j])
            {
                m_valid = false;
                break;
            }
        }
        if (!m_valid)
            break;
    }
}

SwampCooler2560::SwampCooler2560( const SC2560PM& _pm ) :
    m_pm(_pm),
    m_state(Disabled::getInstance()),
    m_power_switch(m_pm.power_switch, INPUT_PULLUP),
    m_joystick(m_pm.joystick_Rx, m_pm.joystick_Ry),
    m_yellow(m_pm.led_yellow),
    m_green(m_pm.led_green),
    m_blue(m_pm.led_blue),
    m_red(m_pm.led_red),
    m_lcd(m_pm.lcd_rs, m_pm.lcd_en, m_pm.lcd_d4, m_pm.lcd_d5, m_pm.lcd_d6, m_pm.lcd_d7),
    m_dht11(m_pm.dht11),
    m_water_sensor(m_pm.water_sensor),
    m_rtc(),
    m_fan_motor(m_pm.fan_motor),
    m_vent_servo()
{
    if (m_pm.is_valid())
    {
        m_state->init(*this);
    }
    else
    {
        abort();
    }
}

void SwampCooler2560::begin()
{
    Serial.begin(9600);

    //Initialize LCD along with it's Wire helper
    m_lcd.begin(16, 2);
    Wire.begin();

    m_vent_servo.attach(m_pm.vent_servo);
    m_servo_pos = m_vent_servo.read();

    m_water_sensor.setup();
}

void SwampCooler2560::update()
{
    m_err = poll_peripherals();
    m_state->loop(*this);
}

bool SwampCooler2560::poll_peripherals()
{
    //Poll power switch
    m_power_switch.update();

    //Update indefinite sensors and peripherals if it is time to do so.
    uint32_t now = millis();

    if (now - m_dht11_last > m_dht11_delay)
    {
        uint8_t chk = m_dht11.read(&m_temp, &m_humidity, NULL);
        m_dht11_last = now;
    }

    if (now - m_vent_servo_last > m_vent_servo_delay)
    {
        uint16_t y = m_joystick.read(Y);

        if (y == 0)
        {
            if (m_servo_pos < 180)
                m_vent_servo.write(++m_servo_pos);
        }
        else if (y == 1023)
            if (m_servo_pos > 0)
                m_vent_servo.write(--m_servo_pos);

        m_vent_servo_last = now;
    }

    if (now - m_water_sensor_last > m_water_sensor_delay)
    {
        m_water_level = m_water_sensor.read_level();
        m_water_sensor_last = now;
    }
}

void SwampCooler2560::display_temp_hum()
{
    char t[16];
    char h[16];
    sprintf(t, "TEMP (C): %d", m_temp);
    m_lcd.setCursor(0, 0);
    m_lcd.print(t);
    sprintf(h, "HUM (pct): %d", m_humidity);
    m_lcd.setCursor(0, 1);
    m_lcd.print(h);
}

void SwampCooler2560::display_water_error()
{
    char t[16];
    char h[16];
    sprintf(t, "ERROR:");
    m_lcd.setCursor(0, 0);
    m_lcd.print(t);
    sprintf(h, "WATER LEVEL LOW");
    m_lcd.setCursor(0, 1);
    m_lcd.print(h);
}

void SwampCooler2560::change_state(State* _next)
{
    if (m_state != nullptr)
    {
        bool century;
        bool h12Flag;
        bool pmFlag;

        Serial.print(m_rtc.getYear(), DEC);
        Serial.print("-");
        Serial.print(m_rtc.getMonth(century), DEC);
        Serial.print("-");
        Serial.print(m_rtc.getDate(), DEC);
        Serial.print(" ");
        Serial.print(m_rtc.getHour(h12Flag, pmFlag), DEC); //24-hr
        Serial.print(":");
        Serial.print(m_rtc.getMinute(), DEC);
        Serial.print(":");
        Serial.print(m_rtc.getSecond(), DEC);
        Serial.print(" | ");

        char msg[INT8_MAX];
        sprintf(msg, "%s -> %s", m_state->m_id, _next->m_id);
        Serial.println(msg);

        m_state->cleanup(*this);
        m_state = _next;
        m_state->init(*this);
    }
}
