#include "Idle.h"
#include "Disabled.h"
#include "Running.h"
#include "Error.h"

Idle* Idle::m_Idle = 0;

void Idle::init(SwampCooler2560& _sc)
{
    _sc.m_green.ON();
}

void Idle::loop(SwampCooler2560& _sc)
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
    else if (_sc.m_temp > _sc.m_temp_threshold)
    {
        _sc.change_state(Running::getInstance());
    }
}

void Idle::cleanup(SwampCooler2560& _sc)
{
    _sc.m_green.OFF();
    _sc.m_lcd.clear();
}