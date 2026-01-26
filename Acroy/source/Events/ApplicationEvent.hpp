#pragma once

#include <cstdint>
#include "Event.hpp"

namespace Acroy {

    class WindowResizeEvent final : public Event
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}

        inline uint32_t GetWidth() const { return m_width; }
        inline uint32_t GetHeight() const { return m_height; }

        inline std::string ToString() const override
        {
            std::stringstream ss;
			ss << GetName() << ": " << m_width << ", " << m_height;
			return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        uint32_t m_width, m_height;
    };

    class WindowMovedEvent final : public Event
    {
    public:
        WindowMovedEvent(int32_t x, int32_t y) : m_x(x), m_y(y) {}
        inline int32_t GetX() const { return m_x; }
        inline int32_t GetY() const { return m_y; }

        inline std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << m_x << ", " << m_y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        
    private:
        int32_t m_x, m_y;
    };

    class WindowCloseEvent final : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowFocusEvent final : public Event
    {
    public:
        WindowFocusEvent() = default;

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowLostFocusEvent final : public Event
    {
    public:
        WindowLostFocusEvent() = default;

        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppTickEvent final : public Event
    {
    public:
        AppTickEvent() = default;
        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppUpdateEvent final : public Event
    {
    public:
        AppUpdateEvent() = default;
        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppRenderEvent final : public Event
    {
    public:
        AppRenderEvent() = default;
        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}
