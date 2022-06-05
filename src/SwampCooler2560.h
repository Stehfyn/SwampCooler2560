#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <LiquidCrystal.h>
#include <SimpleDHT.h>
#include <DS3231.h>
#include <Wire.h>
#include <AlignedJoy.h>
#include <Servo.h>

#include "peripherals/Peripheral.h"
#include "peripherals/Button.h"
#include "peripherals/LED.h"
#include "peripherals/Motor.h"
#include "peripherals/waterSensor.h"

/**
 * Pin Map structure to aid in class construction and program safety.
 *
 * As peripherals are implemented and their mapping's known,
 * they should be added here.
 */

struct SwampCooler2560PinMap
{
public:
    const uint8_t power_switch;

    const uint8_t joystick_Rx;
    const uint8_t joystick_Ry;

    const uint8_t led_yellow;
    const uint8_t led_green;
    const uint8_t led_blue;
    const uint8_t led_red;

    const uint8_t lcd_rs;
    const uint8_t lcd_en;
    const uint8_t lcd_d4;
    const uint8_t lcd_d5;
    const uint8_t lcd_d6;
    const uint8_t lcd_d7;

    const uint8_t dht11;
    const uint8_t water_sensor;

    const uint8_t rtcSDA;
    const uint8_t rtcSCL;

    const uint8_t fan_motor;
    const uint8_t vent_servo;

    SwampCooler2560PinMap(

        const uint8_t _power_switch = 7,

        const uint8_t _joystick_Rx  = A0,
        const uint8_t _joystick_Ry  = A1,

        const uint8_t _led_yellow   = 3,
        const uint8_t _led_green    = 4,
        const uint8_t _led_blue     = 5,
        const uint8_t _led_red      = 6,

        const uint8_t _lcd_rs       = 35,
        const uint8_t _lcd_en       = 33,
        const uint8_t _lcd_d4       = 31,
        const uint8_t _lcd_d5       = 29,
        const uint8_t _lcd_d6       = 27,
        const uint8_t _lcd_d7       = 25,

        const uint8_t _dht11        = 22,
        const uint8_t _water_sensor = A2,

        const uint8_t _rtcSDA       = SDA,
        const uint8_t _rtcSCL       = SCL,

        const uint8_t _fan_motor    = 2,
        const uint8_t _vent_servo   = 13);

  inline bool is_valid() const { return m_valid; }

private:
    bool m_valid;
};

/**
 * Main class encapsulating a Swamp Cooler's peripherals and "globals".
 *
 * The Swamp Cooler uses Singleton "State" classes to handle operation.
 * Only deliberately defined friend states have access to Swamp Cooler members.
 */

class State;

class SwampCooler2560
{
    friend class Disabled;
    friend class Idle;
    friend class Running;
    friend class Error;
    using SC2560PM = SwampCooler2560PinMap;

public:
    explicit SwampCooler2560( const SC2560PM& _pm = SC2560PM() );
    ~SwampCooler2560(){}

    void begin();
    void update();

    SwampCooler2560( const SwampCooler2560& sc ) = delete;
    SwampCooler2560( SwampCooler2560&& sc ) = delete;
    SwampCooler2560& operator=( const SwampCooler2560& sc ) = delete;
    SwampCooler2560& operator=( const SwampCooler2560&& sc ) = delete;

private:
    bool poll_peripherals();
    void display_temp_hum();
    void display_water_error();
    void change_state( State* _next );

private:
    Button        m_power_switch;
    AlignedJoy    m_joystick;

    LED           m_yellow;
    LED           m_green;
    LED           m_blue;
    LED           m_red;

    LiquidCrystal m_lcd;
    SimpleDHT11   m_dht11;
    WaterSensor   m_water_sensor;
    DS3231        m_rtc;
    Motor         m_fan_motor;
    Servo         m_vent_servo;

private:
    int8_t         m_temp               { 0 };
    uint8_t        m_servo_pos          { 0 };
    uint8_t        m_humidity           { 0 };
    uint16_t       m_water_level        { 0 };

    const int8_t   m_temp_threshold     { 30 };  // Celsius
    const uint16_t m_water_threshold    { 200 }; // ATmega2560 ADC = 10 bits = Threshold/1024

    const uint32_t m_dht11_delay        { 1000 };
    uint32_t       m_dht11_last         { 0 };

    const uint32_t m_vent_servo_delay   { 15 };
    uint32_t       m_vent_servo_last    { 0 };

    const uint32_t m_water_sensor_delay { 1000 };
    uint32_t       m_water_sensor_last  { 0 };

private:
    State*         m_state;
    const SC2560PM m_pm;
    bool           m_err                { false };
};