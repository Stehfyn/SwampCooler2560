#include "LED.h"

bool LED::ON()
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

bool LED::OFF()
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
