#pragma once

#include "Log.hpp"

extern Acroy::Application* Acroy::CreateApplication();

int main(int argc, char** argv)
{
    Acroy::Log::Init();

    auto app = Acroy::CreateApplication();
    app->Run();
    delete app;
    return 0;
}