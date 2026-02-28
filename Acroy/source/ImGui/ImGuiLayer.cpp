#include "AcroyPCH.hpp"
#include "ImGuiLayer.hpp"
#include "Core/Log.hpp"
#include "Core/Application.hpp"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Acroy
{
    void ImGuiLayer::OnAttach()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        const Application& appInstance = Application::GetApplicationInstance();

        ImGui_ImplGlfw_InitForOpenGL(appInstance.GetWindow().GetGlfwWindow(), true);
        ImGui_ImplOpenGL3_Init();
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        ImGuiIO& io = ImGui::GetIO();

        if (io.WantCaptureMouse)
        {
            event.handled |= event.IsInCategory(EventCategoryMouse);
            event.handled |= event.IsInCategory(EventCategoryMouseButton);
        }

        if (io.WantCaptureKeyboard)
        {
            event.handled |= event.IsInCategory(EventCategoryKeyboard);
        }
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
