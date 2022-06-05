#include "WaterSensor.h"

WaterSensor::WaterSensor(uint8_t _pin) : Peripheral(_pin, INPUT)
{
    m_ADMUX = (uint32_t*)ADMUX;
    m_ADCSRA = (uint32_t*)ADCSRA;
    m_ADCSRB = (uint32_t*)ADCSRB;
    m_ADC_DATA = (uint32_t*)ADCL;
}

void WaterSensor::setup()
{
    *m_ADCSRA |= 0b10000000; // set bit   7 to 1 to enable the ADC |= *my_ADCSRA + 0x80 == +=
    *m_ADCSRA &= 0b11011111; // clear bit 5 to 0 to disable the ADC trigger mode
    *m_ADCSRA &= 0b11110111; // clear bit 3 to 0 to disable the ADC interrupt
    *m_ADCSRA &= 0b11111000; // clear bit 2-0 to 0 to set prescaler selection to slow reading
    
    //set up the B register
    *m_ADCSRB &= 0b11110111; // clear bit 3 to 0 to reset the channel and gain bits
    *m_ADCSRB &= 0b11111000; // clear bit 2-0 to 0 to set free running mode
    
    //set up the MUX Register
    *m_ADMUX  &= 0b01111111; // clear bit 7 to 0 for AVCC analog reference
    *m_ADMUX  |= 0b01000000; // set bit   6 to 1 for AVCC analog reference
    *m_ADMUX  &= 0b11011111; // clear bit 5 to 0 for right adjust result
    *m_ADMUX  &= 0b11100000; // clear bit 4-0 to 0 to reset the channel and gain bits
}

uint16_t WaterSensor::read_level()
{
    uint8_t adc_channel_num = m_pin;
      // reset the channel and gain bits
    *m_ADMUX &= 0b11100000;
    
    //clear the channel selection bits
    *m_ADCSRB &= 0b11110111;
    
    // set the channel number
    if(adc_channel_num > 7)
    {
      // set the channel selection bits, but remove the most significant bit (bit 3)
      adc_channel_num -= 8;
      
      // set MUX bit 
      *m_ADCSRB |= 0b00001000;
    }
    
    // set the channel selection bits
    *m_ADMUX  += adc_channel_num;
    
    //set bit ?? of ADCSRA to 1 to start a conversion
    *m_ADCSRA |= 0b01000000;
    
    // wait for the conversion to complete
    while((*m_ADCSRA & 0x40) != 0);
    
    // return the result in the ADC data register
    return *m_ADC_DATA;
}