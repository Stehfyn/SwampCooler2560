#pragma once
#include "Peripheral.h"

class Button : public Peripheral
{
public:
	Button( const uint8_t _pin, int _mode ) : Peripheral( _pin, _mode ) {}
	~Button() {}

	void update();
	void reset();

	inline bool is_pressed() const { return m_pressed; }
	inline bool is_held() const { return m_held; }
	inline bool is_released() const { return m_released; }

private:
	uint32_t last_debounce_time { 0 };
	uint32_t debounce_delay     { 50 };

	bool m_pressed              { false };
	bool m_held                 { false };
	bool m_released             { false };
	bool m_state                { false };
	bool m_old_state            { false };
};