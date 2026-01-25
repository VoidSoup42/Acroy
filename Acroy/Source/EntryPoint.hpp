#pragma once

extern Acroy::Application* Acroy::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Acroy::CreateApplication();
    app->Run();
    delete app;
    return 0;
}