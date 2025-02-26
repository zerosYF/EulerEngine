#include"EditorLayer.h"
#include"ImGuizmo.h"
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
        spec.Width = 0;
        spec.Height = 0;
        m_FrameBuffer = FrameBuffer::Create(spec);
        m_ActiveScene = CreateRef<Scene>();

        auto shader = ResourceLibrary::GetResourceLibrary()->LoadShader("common", "Shaders/Camera/first_test.glsl");
        auto texture2D = ResourceLibrary::GetResourceLibrary()->LoadTexture2D("cube_texture", "Assets/mytextures/container2.png");
        auto material = EulerMaterial::Create();
        material->SetShader(shader);
        material->SetColor(m_Color);
        material->SetTexture(texture2D);

        auto cube = m_ActiveScene->CreateObject("Cube");
        cube.AddComponent<MeshRenderer>();
        cube.GetComponent<MeshRenderer>().Material = material;

        m_MainCamera = m_ActiveScene->CreateObject("Camera");
        m_MainCamera.AddComponent<Camera>(PERSPECTIVE);
        m_MainCamera.GetComponent<Transform>().Position = glm::vec3(0.0f, 0.0f, 3.0f);


        class CameraController:public EulerBehaviour {

        public:
            void OnCreate() {
            }
            void OnDestroy() {
            }
            void OnUpdate(TimerSystem ts) {
                auto& transform = GetComponent<Transform>();
                if (InputSystem::IsKeyDown(KINK_KEY_W)) {
                    transform.Position += glm::vec3(0.0f, 1.0f * ts.GetDeltaTime(), 0.0f);
                }
                if (InputSystem::IsKeyDown(KINK_KEY_A)) {
                    transform.Position += glm::vec3(-1.0f * ts.GetDeltaTime(), 0.0f, 0.0f);
                }
                if (InputSystem::IsKeyDown(KINK_KEY_D)) {
                    transform.Position += glm::vec3(1.0f * ts.GetDeltaTime(), 0.0f, 0.0f);
                }
                if (InputSystem::IsKeyDown(KINK_KEY_S)) {
                    transform.Position += glm::vec3(0.0f, -1.0f * ts.GetDeltaTime(), 0.0f);
                }
            }
        };
        auto& nsc = m_MainCamera.AddComponent<NativeScript>();
        nsc.Bind<CameraController>();

        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OnUpdate(TimerSystem ts)
    {

        FrameBufferSpecifications spec = m_FrameBuffer->GetSpecifications();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
            m_FrameBuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveScene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
        }

        m_FrameBuffer->Bind();
        {
            if(m_ViewportFocused || m_ViewportHovered)
                m_CameraController.OnUpdate(ts);
        }
        Renderer::ResetStatistic();
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.5f, 1.0f });
            RenderCommand::Clear();
        }

        {
            m_ActiveScene->OnUpdate(ts);
           /* auto texture2D = ResourceLibrary::GetResourceLibrary()->GetTexture2D("cube_texture");
            Renderer::BeginScene(m_MainCamera.GetComponent<Camera>().RendererCamera);
            for (int i = 0; i < 10; i++) {
                float angle = 20.0f * i;
                auto shader = ResourceLibrary::GetResourceLibrary()->GetShader("common");
                Renderer::DrawCube(shader, m_CubePositions[i], glm::vec3(angle), glm::vec3(0.5f), m_Color, texture2D);
            }
            Renderer::EndScene();*/
        }
        m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {


        static bool dockspaceOpen = false;

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
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMinSize.x = 250.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            //ShowDockingDisabledMessage();
        }
        style.WindowMinSize.x = 32.0f;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Files"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                if (ImGui::MenuItem("New")) {
                    NewScene();
                }
                if (ImGui::MenuItem("Open...")) {
                    OpenScene();
                }
                if (ImGui::MenuItem("Save as...")) {
                    SaveSceneAs();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    Application::Get().Close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        

        m_SceneHierarchyPanel.OnImGuiRender();

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
        
        Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused && !m_ViewportHovered);
        ImVec2 size = ImGui::GetContentRegionAvail();
        m_ViewportSize = { size.x, size.y };
        unsigned int textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image(textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

        //gizmos
        GameObject selectedObj = m_SceneHierarchyPanel.GetSelectedGameObject();
        if (selectedObj) {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

            auto cameraObj = m_ActiveScene->GetPrimaryCamera();
            const auto& cameraCom = cameraObj.GetComponent<Camera>();
            const auto& cameraViewMtx = cameraCom.RendererCamera->GetViewMatrix();
            const auto& cameraProjMtx = cameraCom.RendererCamera->GetProjectionMatrix();

            auto& tc = selectedObj.GetComponent<Transform>();
            glm::mat4 transform = tc.GetTransform();
            ImGuizmo::Manipulate(glm::value_ptr(cameraViewMtx), glm::value_ptr(cameraProjMtx),
                ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform));
        }

        ImGui::End();
        ImGui::PopStyleVar();
         
        ImGui::End();

    }

    void EditorLayer::OnEvent(Event& e)
    {
        m_CameraController.OnEvent(e);
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(KINK_BIND_EVENT_FUNC(EditorLayer::OnKeyPressed));
    }
    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        return false;
    }
    void EditorLayer::NewScene()
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }
    void EditorLayer::OpenScene()
    {
        std::string filepath = FileDialogs::OpenFile("Kink Scene (*.kink)\0*.kink\0");
        if (!filepath.empty()) {
            m_ActiveScene = CreateRef<Scene>();
            m_ActiveScene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
            m_SceneHierarchyPanel.SetContext(m_ActiveScene);

            SceneSerializer serializer(m_ActiveScene);
            serializer.Deserialize(filepath);
        }
    }
    void EditorLayer::SaveSceneAs()
    {
        std::string filepath = FileDialogs::SaveFile("Kink Scene (*.kink)\0*.kink\0");
        if (!filepath.empty()) {
            SceneSerializer serializer(m_ActiveScene);
            serializer.Serialize(filepath);
        }
    }
}
