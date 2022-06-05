#pragma once
#include "State.h"

class Error : public State
{
public:
    void init( SwampCooler2560& _sc );
    void loop( SwampCooler2560& _sc );
    void cleanup( SwampCooler2560& _sc );

    static Error* getInstance()
    {
        if (m_Error == nullptr)
        {
            m_Error = new Error();
        }
        return m_Error;
    }

private:
    Error() : State("ERROR") { }
    static Error* m_Error;
};