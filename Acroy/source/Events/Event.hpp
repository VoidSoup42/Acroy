#pragma once

#include <functional>
#include <string>
#include <sstream>

namespace Acroy {

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = 1 << 0,
        EventCategoryInput       = 1 << 1,
        EventCategoryKeyboard    = 1 << 2,
        EventCategoryMouse       = 1 << 3,
        EventCategoryMouseButton = 1 << 4
    };

    #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                                   EventType GetEventType() const override { return EventType::type; } \
                                   const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() const override { return category; }

    class Event
    {
    friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category) const
        {
            return category & GetCategoryFlags();
        }

        bool handled = false;
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event) : m_event(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.handled = func(*(T*)&m_event);
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
    };
}
