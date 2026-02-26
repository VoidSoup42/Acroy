#pragma once

#include "Core/Layer.hpp"
#include <vector>

namespace Acroy
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        inline std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        inline std::vector<Layer*>::iterator end() { return m_layers.end(); }

    private:
        std::vector<Layer*> m_layers;
        std::vector<Layer*>::iterator m_layerInsert;
    };
}
