#pragma once

#include "Core/Input.hpp"

namespace Acroy
{
    class LinuxInput final : public Input
    {
    protected:
        bool IsKeyPressedImpl(int keycode) override;
        bool IsMouseButtonPressedImpl(int button) override;
        glm::vec2 GetMousePositionImpl() override;
        void SetMouseModeImpl(MouseMode mode) override;

    private:
        MouseMode m_mouseMode = MouseMode::Normal;
    };
}
