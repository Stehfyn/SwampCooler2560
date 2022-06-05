#pragma once
#include "State.h"

class Disabled : public State
{
public:
	void init( SwampCooler2560& _sc );
	void loop( SwampCooler2560& _sc );
	void cleanup( SwampCooler2560& _sc );

	static Disabled* getInstance()
	{
		if (m_Disabled == nullptr)
		{
			m_Disabled = new Disabled();
		}
		return m_Disabled;
	}

private:
	Disabled() : State("DISABLED") { }
	static Disabled* m_Disabled;
};