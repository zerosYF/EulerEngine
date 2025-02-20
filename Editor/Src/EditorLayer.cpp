#include"EditorLayer.h"
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace EulerEngine {
    EditorLayer::EditorLayer() :EulerLayer("EditorLayer"), m_ViewportSize(0, 0), m_CameraController(PERSPECTIVE)
    {
    }
    void EditorLayer::OnDetach()
    {
        Renderer::ShutDown();
    }

    void EditorLayer::OnAttach()
    {
        Renderer::Init();

        FrameBufferSpecifications spec;
        spec.Width = 1280;
        spec.Height = 720;
        m_FrameBuffer = FrameBuffer::Create(spec);
        m_ActiveScene = CreateRef<Scene>();
        auto cube = m_ActiveScene->CreateObject("Cube");
        cube.AddComponent<RendererComponent>();

        m_Camera = m_ActiveScene->CreateObject("Camera");
        m_Camera.AddComponent<CameraComponent>(PERSPECTIVE);
        m_Camera.GetComponent<TransformComponent>().Position = glm::vec3(0.0f, 0.0f, 3.0f);
    }

    void EditorLayer::OnUpdate(TimerSystem ts)
    {
        if (InputSystem::IsKeyDown(KINK_KEY_W)) {
            m_Camera.GetComponent<TransformComponent>().Position += glm::vec3(0.0f, 1.0f * ts.GetDeltaTime(), 0.0f);
        }
        if (InputSystem::IsKeyDown(KINK_KEY_A)) {
            m_Camera.GetComponent<TransformComponent>().Position += glm::vec3(-1.0f * ts.GetDeltaTime(), 0.0f, 0.0f);
        }
        if (InputSystem::IsKeyDown(KINK_KEY_D)) {
            m_Camera.GetComponent<TransformComponent>().Position += glm::vec3(1.0f * ts.GetDeltaTime(), 0.0f, 0.0f);
        }
        if (InputSystem::IsKeyDown(KINK_KEY_S)) {
            m_Camera.GetComponent<TransformComponent>().Position += glm::vec3(0.0f, -1.0f * ts.GetDeltaTime(), 0.0f);
        }

        m_FrameBuffer->Bind();
        {
            if(m_ViewportFocused || m_ViewportHovered)
                m_CameraController.OnUpdate(ts);
        }
        Renderer::ResetStatistic();
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();
        }

        {
            m_ActiveScene->OnUpdate(ts);
            /*Renderer::BeginScene(m_CameraController.GetCamera());
            for (int i = 0; i < 10; i++) {
                float angle = 20.0f * i;
                auto material = ResourceLibrary::GetResourceLibrary()->GetMaterial("first");
                material->SetColor(m_Color);
                Renderer::DrawCube(m_CubePositions[i], glm::vec3(angle), glm::vec3(0.5f), material);
            }
            Renderer::EndScene();*/
        }
        m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {


        static bool dockspaceOpen = true;

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            //ShowDockingDisabledMessage();
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
                if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
                if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false, dockspaceOpen != NULL))
                    dockspaceOpen = false;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_Color));
        ImGui::Text("Renderer Info:");
        ImGui::Text("Draw Calls: %d", Renderer::GetStats().DrawCalls);
        ImGui::Text("Cubes: %d", Renderer::GetStats().CubeCount);
        ImGui::Text("Vertices: %d", Renderer::GetStats().GetTotalVertexCount());
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport"); 
        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        //KINK_CORE_WARN("Focused: {0}", m_ViewportFocused);
        //KINK_CORE_WARN("Hovered: {0}", m_ViewportHovered);
        Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused && !m_ViewportHovered);
        ImVec2 size = ImGui::GetContentRegionAvail();
        if (m_ViewportSize.x != size.x || m_ViewportSize.y != size.y) {
            m_ViewportSize = { size.x, size.y };
            m_FrameBuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
        }
        unsigned int textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image(textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
        ImGui::PopStyleVar();
         
        ImGui::End();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        m_CameraController.OnEvent(e);
    }
}
