#pragma once

#include "Events/Event.hpp"

namespace Acroy {
    class Layer
    {
    public:
        virtual ~Layer() {};

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate() {};
        virtual void OnEvent(Event& event) {};
    };
}
