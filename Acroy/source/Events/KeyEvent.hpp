#pragma once

#include "Event.hpp"
#include <cstdint>

namespace Acroy {
    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_keycode; }
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keycode) : m_keycode(keycode) {}
        int m_keycode;
    };

    class KeyPressedEvent final : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, uint32_t repeatCount)
        : m_repeatCount(repeatCount)
        , KeyEvent(keycode) {}

        inline uint32_t GetRepeatCount() const { return m_repeatCount; }        
        inline std::string ToString() const override
        {
            std::stringstream ss;
			ss << GetName() << ": " << m_keycode << " (" << m_repeatCount << " repeats";
			return ss.str();
        }
        
        EVENT_CLASS_TYPE(KeyPressed)

    private:
        uint32_t m_repeatCount;
    };

    class KeyReleasedEvent final : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        inline std::string ToString() const override
        {
            std::stringstream ss;
			ss << GetName() << ": " << m_keycode;
			return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}
