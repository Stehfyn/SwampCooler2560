#pragma once
#include "../SwampCooler2560.h"

class State
{
public:
    virtual void init( SwampCooler2560& _sc ) = 0;
    virtual void loop( SwampCooler2560& _sc ) = 0;
    virtual void cleanup( SwampCooler2560& _sc ) = 0;
    ~State(){}

public:
    const uint8_t* m_id;

protected:
    State(const uint8_t* _id) : m_id(_id) { }

};