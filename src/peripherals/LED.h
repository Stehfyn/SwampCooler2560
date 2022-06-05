#pragma once
#include "Peripheral.h"

class LED : public Peripheral
{
public:
    LED( uint8_t _pin ) : Peripheral( _pin, OUTPUT ) {}
    ~LED() {}

    bool ON();
    bool OFF();
};