#include <Acroy.hpp>

class GameLayer : public Acroy::Layer
{
    void OnAttach() override
    {
        ACROY_INFO("Game Attached");
    }

    void OnDetach() override
    {
        ACROY_INFO("Game detached");
    }

    void OnUpdate() override
    {
        // ACROY_INFO("Game Updating");
    }

    void OnEvent(Acroy::Event& event) override
    {
        ACROY_TRACE(event.ToString());
    }
};

class Sandbox : public Acroy::Application
{
public:
    Sandbox()
    {   
        PushLayer(new GameLayer);
    }

    ~Sandbox()
    {
        
    }
};

Acroy::Application* Acroy::CreateApplication()
{
    return new Sandbox();
}