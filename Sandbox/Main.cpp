#include <Acroy.hpp>

int main()
{
    Acroy::Window window(800, 600, "Acroy Sandbox", false);

    while (!window.ShouldClose())
    {
        window.SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        window.Update();
    }

    return 0;
}