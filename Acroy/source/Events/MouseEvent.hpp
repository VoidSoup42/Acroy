#pragma once

#include "Event.hpp"

namespace Acroy {

    class MouseButtonEvent : public Event
    {
    public:
        inline int GetButton() const { return m_button; }
        EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(int button) : m_button(button) {}
        int m_button;
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        inline std::string ToString() const override
        {
            return std::string(GetName()) + ": " + std::to_string(m_button);
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent final : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        inline std::string ToString() const override
        {
            return std::string(GetName()) + ": " + std::to_string(m_button);
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(float mouseX, float mouseY) : m_mouseX(mouseX), m_mouseY(mouseY) {}

        inline float GetX() const { return m_mouseX; }
        inline float GetY() const { return m_mouseY; }

        inline std::string ToString() const override
        {
            std::stringstream ss;
			ss << GetName() << ": " << m_mouseX << ", " << m_mouseY;
			return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_mouseX, m_mouseY;
    };

    class MouseScrolledEvent final : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

        inline float GetXOffset() const { return m_xOffset; }
        inline float GetYOffset() const { return m_yOffset; }

        inline std::string ToString() const override
        {
            std::stringstream ss;
			ss << GetName() << ": " << m_xOffset << ", " << m_yOffset;
			return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_xOffset, m_yOffset;
    };
}
