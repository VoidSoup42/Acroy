#pragma once

#include <glm/glm.hpp>

namespace Acroy {

    enum class MouseMode
    {
        Normal,
        Hidden,
        Disabled
    };

    class Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static glm::vec2 GetMousePosition();
        static void SetMouseMode(MouseMode mode);

    private:
        static MouseMode m_mouseMode;
    };
}
