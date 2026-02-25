#include <Acroy.hpp>
#include "SandboxLayer.hpp"

class App : public Acroy::Application
{
public:
    App()
    {
        PushLayer(new SandboxLayer);
    }
};

Acroy::Application* Acroy::CreateApplication()
{
    return new App();
}
