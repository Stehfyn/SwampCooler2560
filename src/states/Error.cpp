#include "Error.h"
#include "Idle.h"
#include "Disabled.h"
#include "Running.h"

Error* Error::m_Error = 0;

void Error::init(SwampCooler2560& _sc)
{
    _sc.m_red.ON();
}

void Error::loop(SwampCooler2560& _sc)
{
    _sc.display_water_error();

    if (_sc.m_power_switch.is_released())
    {
        _sc.change_state(Disabled::getInstance());
    }
    else if (_sc.m_water_level > _sc.m_water_threshold)
    {
        _sc.change_state(Idle::getInstance());
    }
}

void Error::cleanup(SwampCooler2560& _sc)
{
    _sc.m_red.OFF();
    _sc.m_lcd.clear();
}