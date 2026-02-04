#pragma once

#include "Events/Event.hpp"
#include "Core/Timestep.hpp"

namespace Acroy {
    class Layer
    {
    public:
        virtual ~Layer() {};

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate(Timestep timestep) {};
        virtual void OnEvent(Event& event) {};
    };
}
