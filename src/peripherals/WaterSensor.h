#pragma once
#include "Peripheral.h"

class WaterSensor : public Peripheral
{
public:
    WaterSensor( uint8_t _pin );
    ~WaterSensor() {}

    void setup();
    uint16_t read_level();

private:
    volatile uint32_t* m_ADMUX; //= (unsigned char)0x7C;
    volatile uint32_t* m_ADCSRB; //= (unsigned char)0x7B;
    volatile uint32_t* m_ADCSRA;//= (unsigned char)0x7A;
    volatile uint32_t* m_ADC_DATA;//= (unsigned short)0x78;
};