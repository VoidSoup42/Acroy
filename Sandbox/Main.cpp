#include <Acroy.hpp>

int main()
{
    Acroy::ApplicationProps appProps;
    appProps.title = "Application";
    appProps.windowWidth = 1280;
    appProps.windowHeight = 720;
    appProps.fullscreen = false;
    appProps.vSync = false;

    Acroy::Application app(appProps);
    app.Run();

    return 0;
}