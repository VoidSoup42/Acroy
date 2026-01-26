#include <Acroy.hpp>

class Sandbox : public Acroy::Application
{
public:
    Sandbox()
    {   
        
    }

    ~Sandbox()
    {
        
    }
};

Acroy::Application* Acroy::CreateApplication()
{
    return new Sandbox();
}