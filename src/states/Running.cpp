#include "Running.h"
#include "Disabled.h"
#include "Idle.h"
#include "Error.h"

Running* Running::m_Running = 0;

void Running::init(SwampCooler2560& _sc)
{
    _sc.m_blue.ON();
    _sc.m_fan_motor.ON();
}

void Running::loop(SwampCooler2560& _sc)
{
    _sc.display_temp_hum();

    if (_sc.m_power_switch.is_released())
    {
        _sc.change_state(Disabled::getInstance());
    }
    else if (_sc.m_water_level < _sc.m_water_threshold)
    {
        _sc.change_state(Error::getInstance());
    }
    else if (_sc.m_temp < _sc.m_temp_threshold)
    {
        _sc.change_state(Idle::getInstance());
    }
}

void Running::cleanup(SwampCooler2560& _sc)
{
    _sc.m_blue.OFF();
    _sc.m_fan_motor.OFF();
    _sc.m_lcd.clear();
}