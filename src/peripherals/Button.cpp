#include "Button.h"

void Button::update()
{
    bool reading = false;

    if (m_mode == INPUT)
    {
        reading = (*m_in & m_bit);
    }
    else if (m_mode == INPUT_PULLUP)
    {
        reading = (*m_in & m_bit) ? LOW : HIGH;
    }

    m_pressed = false;
    m_released = false;

    if (reading != m_old_state)
    {
        last_debounce_time = millis();
    }

    if (millis() - last_debounce_time > debounce_delay)
    {
        if (reading != m_state)
        {
            m_state = reading;
            if (m_state)
            {
                m_pressed = !m_held;
                m_held = true;
            }
            else
            {
                m_released = true;
                m_held = false;
            }
        }
    }

    m_old_state = reading;
}
void Button::reset()
{
    m_pressed = false;
    m_held = false;
    m_pressed = false;

    m_state = false;
    m_old_state = false;
}