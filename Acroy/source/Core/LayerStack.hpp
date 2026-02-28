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
        void PushOverlay(Layer* overlay);
        void PopOverlay(Layer* overlay);

        inline std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        inline std::vector<Layer*>::iterator end() { return m_layers.end(); }
        inline std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
        inline std::vector<Layer*>::reverse_iterator rend()   { return m_layers.rend(); }

    private:
        std::vector<Layer*> m_layers;
        uint32_t m_layerInsertIndex = 0;
    };
}
