/**
*	Name:		Idle.h
*	Purpose:	Declares the SwampCooler2560's "Idle" state.
*/
#pragma once
#include "State.h"

class Idle : public State
{
public:
	void init( SwampCooler2560& _sc );
	void loop( SwampCooler2560& _sc );
	void cleanup( SwampCooler2560& _sc );

	static Idle* getInstance()
	{
		if (m_Idle == nullptr)
		{
			m_Idle = new Idle();
		}
		return m_Idle;
	}

private:
	Idle() : State("IDLE") { }
	static Idle* m_Idle;
};