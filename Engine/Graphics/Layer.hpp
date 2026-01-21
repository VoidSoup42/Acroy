#pragma once

namespace Acroy {
    class Layer
    {
    public:
        virtual ~Layer(){};

        virtual void OnAttach(){};
        virtual void OnDetach(){};
        virtual void OnUpdate(float deltaTime){};
    };
}
