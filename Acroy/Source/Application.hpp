#pragma once

namespace Acroy {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication(); // Defined in Client
}
