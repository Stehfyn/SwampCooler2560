#include "Peripheral.h"

Peripheral::Peripheral( const uint8_t _pin, int _mode ) : 
	m_bit( digitalPinToBitMask( _pin ) ),
	m_port( digitalPinToPort( _pin ) ),
	m_mode( _mode )
{
	m_reg = portModeRegister(m_port);
	m_in = portInputRegister(m_port);
	m_out = portOutputRegister(m_port);

	if (_mode == INPUT)
	{
		*m_reg &= ~m_bit;
		*m_in &= ~m_bit;
	}
	else if (_mode == OUTPUT)
	{
		*m_reg |= m_bit;
		*m_out &= ~m_bit;
	}
	else if (_mode == INPUT_PULLUP)
	{
		*m_reg &= ~m_bit;
		*m_out |= m_bit;
	}
}