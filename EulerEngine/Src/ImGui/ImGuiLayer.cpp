#include "gkpch.h"
#include "ImGuiLayer.h"
#define IMGUI_IMPL_API
#include "backends/imgui_impl_opengl3_loader.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "GutKink/Application.h"
#include <GLFW/glfw3.h>
#include "ImGuizmo.h"
EulerEngine::ImGuiLayer::ImGuiLayer():EulerLayer("ImGuiLayer") {

}
void EulerEngine::ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors | ImGuiBackendFlags_HasSetMousePos;

    io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/calibri.ttf", 15.0f);

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    SetDarkThemeColors();
    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void EulerEngine::ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void EulerEngine::ImGuiLayer::OnImGuiRender() 
{
    
}
void EulerEngine::ImGuiLayer::OnEvent(Event& e)
{
    if (m_BlockEvents) {
        ImGuiIO& io = ImGui::GetIO();
        e.m_Handled |= e.IsInCategory(KINK_EVENT_CATEGORY_MOUSE) & io.WantCaptureMouse;
        e.m_Handled |= e.IsInCategory(KINK_EVENT_CATEGORY_KEYBOARD) & io.WantCaptureKeyboard;
    }
}
void EulerEngine::ImGuiLayer::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}
void EulerEngine::ImGuiLayer::End() {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void EulerEngine::ImGuiLayer::SetDarkThemeColors()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
    style.Colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    style.Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };    
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    style.Colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    style.Colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.4f, 0.405f, 0.41f, 1.0f };
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.5f, 0.505f, 0.51f, 1.0f };
    style.Colors[ImGuiCol_CheckMark] = ImVec4{ 0.9f, 0.905f, 0.91f, 1.0f };
    style.Colors[ImGuiCol_SliderGrab] = ImVec4{ 0.5f, 0.505f, 0.51f, 1.0f };
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_Button] = ImVec4{ 0.5f, 0.505f, 0.51f, 1.0f };
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_Header] = ImVec4{ 0.4f, 0.405f, 0.41f, 1.0f };
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.4f, 0.405f, 0.41f, 1.0f };
    style.Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.5f, 0.505f, 0.51f, 1.0f };
    style.Colors[ImGuiCol_Separator] = ImVec4{ 0.5f, 0.505f, 0.51f, 1.0f };
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.5f, 0.505f, 0.51f, 1.0f };
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_Tab] = ImVec4{ 0.5f, 0.505f, 0.51f, 1.0f };
    style.Colors[ImGuiCol_TabHovered] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_TabActive] = ImVec4{ 0.6f, 0.605f, 0.61f, 1.0f };
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    style.Colors[ImGuiCol_DockingPreview] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    style.Colors[ImGuiCol_PlotLines] = ImVec4{ 0.4f, 0.39f, 0.38f, 0.6f };
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4{ 0.25f, 1.0f, 0.0f, 1.0f };
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4{ 0.4f, 0.39f, 0.38f, 0.6f };
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4{ 0.25f, 1.0f, 0.0f, 1.0f };
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4{ 0.25f, 1.0f, 0.0f, 0.4f };
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4{ 1.0f, 0.0f, 0.0f, 0.9f };
    style.Colors[ImGuiCol_NavHighlight] = ImVec4{ 0.26f, 0.59f, 0.98f, 1.0f };
}
