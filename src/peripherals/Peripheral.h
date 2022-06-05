#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Peripheral
{
public:
	~Peripheral() {}

protected:
	Peripheral( const uint8_t _pin, int _mode );

	uint8_t           m_bit;
	uint8_t           m_pin;
	uint8_t           m_mode;
	uint8_t           m_port;

	volatile uint8_t* m_reg; //ddr
	volatile uint8_t* m_in;  //pin
	volatile uint8_t* m_out; //port
};