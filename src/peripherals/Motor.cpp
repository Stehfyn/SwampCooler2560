#include "Motor.h"

bool Motor::ON()
{
    if (m_mode == OUTPUT)
    {
        *m_out |= m_bit;
        return true;
    }
    else
    {
        return false;
    }
}

bool Motor::OFF()
{
    if (m_mode == OUTPUT)
    {
        *m_out &= ~m_bit;
        return true;
    }
    else
    {
        return false;
    }
}
