#pragma once
#include "State.h"

class Running : public State
{
public:
	void init( SwampCooler2560& _sc );
	void loop( SwampCooler2560& _sc );
	void cleanup( SwampCooler2560& _sc );

	static Running* getInstance()
	{
		if (m_Running == nullptr)
		{
			m_Running = new Running();
		}
		return m_Running;
	}

private:
	Running() : State("RUNNING") {}
	static Running* m_Running;
};