#include <Acroy.hpp>

int main()
{
    Acroy::Window window(1280, 720, "Application", false);

    while (!window.ShouldClose())
    {
        window.SetClearColor({0.4, 0.05, 0.7, 1.0});
        window.Update();
    }
    
    return 0;
}
