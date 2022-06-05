#pragma once
#include "Peripheral.h"

class Motor : public Peripheral
{
public:
    Motor( uint8_t _pin ) : Peripheral(_pin, OUTPUT) {}
    ~Motor() {}

    bool ON();
    bool OFF();
};