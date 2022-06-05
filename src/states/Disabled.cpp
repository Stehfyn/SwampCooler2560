#include "Disabled.h"
#include "Idle.h"

Disabled* Disabled::m_Disabled = 0;

void Disabled::init(SwampCooler2560& _sc)
{
    _sc.m_yellow.ON();
}

void Disabled::loop(SwampCooler2560& _sc)
{
    if (_sc.m_power_switch.is_released())
    {
        _sc.change_state(Idle::getInstance());
    }
}

void Disabled::cleanup(SwampCooler2560& _sc)
{
    _sc.m_yellow.OFF();
    _sc.m_lcd.clear();
}