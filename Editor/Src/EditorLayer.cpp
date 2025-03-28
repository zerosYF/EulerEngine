#include"EditorLayer.h"
#include"ImGuizmo.h"
namespace EulerEngine {
    EditorLayer::EditorLayer() :EulerLayer("EditorLayer"), m_ViewportSize(0, 0), m_EditorCameraController(),m_ViewportBounds()
    {
    }
    void EditorLayer::OnDetach()
    {
        Renderer::ShutDown();
    }

    void EditorLayer::OnAttach()
    {
        Renderer::Init();  //此方法应该放在application中

        m_IconPlay = Texture2D::Create("Assets/Editor/Icons/PlayButton.png");
        m_IconStop = Texture2D::Create("Assets/Editor/Icons/StopButton.png");
        m_IconSimulate = Texture2D::Create("Assets/Editor/Icons/SimulateButton.png");
        m_IconPause = Texture2D::Create("Assets/Editor/Icons/PauseButton.png");
        m_IconStep = Texture2D::Create("Assets/Editor/Icons/StepButton.png");

        FrameBufferSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;
        spec.Attachments = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::Depth };
        m_FrameBuffer = FrameBuffer::Create(spec);

        m_EditorScene = CreateRef<Scene>();
        m_ActiveScene = m_EditorScene;

        auto commandArgs = Application::Get().GetSpecification().CmdArgs;
        if (commandArgs.Count > 1) {
            auto projectFilePath = commandArgs[1];
            OpenProject(projectFilePath);
        }
        else {
            if (!OpenProject()) {
                Application::Get().Close();
            }
        }
    }

    void EditorLayer::OnUpdate()
    {
        FrameBufferSpecification spec = m_FrameBuffer->GetSpecifications();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
            m_FrameBuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
            m_EditorCameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveScene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
        }

        m_FrameBuffer->Bind();
        Renderer::ResetStatistic();
        {
            RenderCommand::SetClearColor(m_Color);
            RenderCommand::Clear();
            m_FrameBuffer->ClearAttachment(1, -1);
        }

        {
            switch (m_SceneState) {
            case SceneState::Edit:
                if (m_ViewportFocused || m_ViewportHovered)
                    m_EditorCameraController.OnUpdate();
                m_ActiveScene->OnUpdateEditor(m_EditorCameraController.GetCamera());
                break;
            case SceneState::Play:
                m_ActiveScene->OnUpdateRuntime();
                break;
            case SceneState::Simulate:
                m_ActiveScene->OnUpdateSimulation(m_EditorCameraController.GetCamera());
                break;
            }
        }

        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        my = viewportSize.y - my;
        int mouseX = (int)mx;
        int mouseY = (int)my;
        //KINK_CORE_TRACE("Mouse Position: {0}, {1}", mouseX, mouseY);
        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
        {
            int pixelData = m_FrameBuffer->ReadPixel(1, mouseX, mouseY);
            //KINK_CORE_TRACE("Pixel Data: {0}", pixelData);
            if (pixelData != -1) {
                m_HoveredGameObject = {(entt::entity)pixelData, m_ActiveScene.get()};
            }
            else {
                m_HoveredGameObject = {};
            }
        }
        OnOverlayRender();

        m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {


        static bool dockspaceOpen = false;

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
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

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

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
                if (ImGui::MenuItem("Open Project")) {
                    OpenProject();
                }

                ImGui::Separator();
                if (ImGui::MenuItem("New Scene")) {
                    NewScene();
                }
                if (ImGui::MenuItem("Open Scene...")) {
                    OpenScene();
                }
                if (ImGui::MenuItem("Save Scene as...")) {
                    SaveSceneAs();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    Application::Get().Close();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Script")) {
                if (ImGui::MenuItem("Reload")) {
                    ScriptEngine::ReloadAssembly();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        

        m_SceneHierarchyPanel.OnImGuiRender();
        m_AssetBrowserPanel->OnImGuiRender();

        ImGui::Begin("Statistics");
        ImGui::Text("Hovered Object: %s", m_HoveredGameObject? m_HoveredGameObject.GetComponent<Profile>().Tag.c_str() : "None");
        ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_Color));
        ImGui::Text("Renderer Info:");
        ImGui::Text("Draw Calls: %d", Renderer::GetStats().DrawCalls);
        ImGui::Text("Cubes: %d", Renderer::GetStats().CubeCount);
        ImGui::Text("Quads: %d", Renderer::GetStats().QuadCount);
        ImGui::Text("Rect: %d", Renderer::GetStats().RectCount);
        ImGui::Text("Circles: %d", Renderer::GetStats().CircleCount);
        ImGui::Text("Lines: %d", Renderer::GetStats().LineCount);
        ImGui::Text("Vertices: %d", Renderer::GetStats().GetTotalVertexCount());
        ImGui::Text("Indices: %d", Renderer::GetStats().GetTotalIndexCount());
        ImGui::End();

        ImGui::Begin("Gizmos");
        ImGui::Checkbox("Show Physics Colliders", &m_ShowPhysicsColliders);
        ImGui::ColorEdit4("Physics Visible Color", glm::value_ptr(m_PhysicsVisibleColor));
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport"); 
        auto viewportOffset = ImGui::GetCursorPos();

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        
        Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportHovered);
        ImVec2 size = ImGui::GetContentRegionAvail();
        m_ViewportSize = { size.x, size.y };
        unsigned int textureID = m_FrameBuffer->GetColorAttachmentRendererID(0);
        ImGui::Image(textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetBrowserItem")) {
                const wchar_t* path = (const wchar_t*)payload->Data;
                OpenScene(path);
            }
            ImGui::EndDragDropTarget();
        }

        auto windowSize = ImGui::GetWindowSize();
        ImVec2 minBound = ImGui::GetWindowPos();
        minBound.x += viewportOffset.x;
        minBound.y += viewportOffset.y;
        ImVec2 maxBound = { minBound.x + size.x, minBound.y + size.y };
        m_ViewportBounds[0] = { minBound.x, minBound.y };
        m_ViewportBounds[1] = { maxBound.x, maxBound.y };

        if (m_SceneState == SceneState::Edit) {
            //gizmos
            GameObject selectedObj = m_SceneHierarchyPanel.GetSelectedGameObject();
            if (selectedObj && m_GizmosType != -1) {
                ImGuizmo::SetOrthographic(true);
                ImGuizmo::SetDrawlist();
                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

                const auto& cameraViewMtx = m_EditorCameraController.GetCamera().GetViewMatrix();
                const auto& cameraProjMtx = m_EditorCameraController.GetCamera().GetProjectionMatrix();

                auto& tc = selectedObj.GetComponent<Transform>();
                glm::mat4 transform = tc.GetTransform();

                bool snap = InputSystem::IsKeyDown(KINK_KEY_LEFT_CONTROL);
                float snapValue = 0.5f;
                if (m_GizmosType == ImGuizmo::OPERATION::ROTATE) {
                    snapValue = 45.0f;
                }
                float snapValues[3] = { snapValue, snapValue, snapValue };

                ImGuizmo::Manipulate(glm::value_ptr(cameraViewMtx), glm::value_ptr(cameraProjMtx),
                    (ImGuizmo::OPERATION)m_GizmosType, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform),
                    nullptr, snap ? snapValues : nullptr);
                if (ImGuizmo::IsUsing()) {
                    glm::vec3 translation, rotation, scale;
                    Math::DecomposeTransform(transform, translation, rotation, scale);
                    glm::vec3 deltaRotation = rotation - tc.Rotation;
                    tc.Rotation += deltaRotation;
                    tc.Position = translation;
                    tc.Scale = scale;
                }
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

        UI_Toolbar();
         
        ImGui::End();

    }

    void EditorLayer::OnEvent(Event& e)
    {
        if (m_SceneState == SceneState::Edit) {
            m_EditorCameraController.OnEvent(e);
        }
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(KINK_BIND_EVENT_FUNC(EditorLayer::OnKeyPressed));
        dispatcher.Dispatch<MouseButtonPressedEvent>(KINK_BIND_EVENT_FUNC(EditorLayer::OnMouseButtonPressed));
    }
    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        bool control = InputSystem::IsKeyDown(KINK_KEY_LEFT_CONTROL) || InputSystem::IsKeyDown(KINK_KEY_RIGHT_CONTROL);
        bool shift = InputSystem::IsKeyDown(KINK_KEY_LEFT_SHIFT) || InputSystem::IsKeyDown(KINK_KEY_RIGHT_SHIFT);
        bool alt = InputSystem::IsKeyDown(KINK_KEY_LEFT_ALT) || InputSystem::IsKeyDown(KINK_KEY_RIGHT_ALT);
        if (e.GetKeyCode() == KINK_KEY_N && control) {
            NewScene();
        }
        if (e.GetKeyCode() == KINK_KEY_O && control) {
            OpenScene();
        }
        if (e.GetKeyCode() == KINK_KEY_S && control) {
            SaveScene();
        }
        if (e.GetKeyCode() == KINK_KEY_D && control) {
            OnDuplicateGameObject();
        }
        if (e.GetKeyCode() == KINK_KEY_P && control) {
            if (m_SceneState != SceneState::Edit) {
                OnSceneStop();
            }
            else {
                OnScenePlay();
            }
        }
        switch (e.GetKeyCode())
        {
        case KINK_KEY_Q:
            m_GizmosType = -1;
            break;
        case KINK_KEY_W:
            m_GizmosType = ImGuizmo::OPERATION::TRANSLATE;
            break;
        case KINK_KEY_E:
            m_GizmosType = ImGuizmo::OPERATION::ROTATE;
            break;
        case KINK_KEY_R:
            m_GizmosType = ImGuizmo::OPERATION::SCALE;
            break;
        default:
            break;
        }
        return false;
    }
    bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
        if (e.GetMouseButton() == KINK_MOUSE_BUTTON_LEFT) {
            if (m_HoveredGameObject && !ImGuizmo::IsOver() && !InputSystem::IsKeyDown(KINK_KEY_LEFT_ALT)) {
                m_SceneHierarchyPanel.SetSeletedGameObject(m_HoveredGameObject);
            }
        }
        return false;
    }
    void EditorLayer::OnOverlayRender()
    {
        if (m_SceneState == SceneState::Play) {
            GameObject cameraObj = m_ActiveScene->GetPrimaryCamera();
            if (!cameraObj) {
                return;
            }
            Renderer::BeginScene(cameraObj.GetComponent<Camera>().RendererCamera);
        }
        else {
            Renderer::BeginScene(m_EditorCameraController.GetCamera());
        }
        if (m_ShowPhysicsColliders) {
            {
                auto view = m_ActiveScene->GetAllEntitiesWith<Transform, BoxCollider2D>();
                for (auto& entity : view) {
                    auto [transform, collider] = view.get<Transform, BoxCollider2D>(entity);
                    glm::vec3 pos = transform.Position + glm::vec3(collider.Offset, 0.001f);
                    glm::vec3 size = glm::vec3(transform.Scale.x * collider.Size.x, transform.Scale.y * collider.Size.y, 1.0f);
                    Renderer::DrawRect(pos, transform.Rotation, size * 2.0f, m_PhysicsVisibleColor);
                }
            }
            {
                auto view = m_ActiveScene->GetAllEntitiesWith<Transform, CircleCollider2D>();
                for (auto& entity : view) {
                    auto [transform, collider] = view.get<Transform, CircleCollider2D>(entity);
                    glm::vec3 pos = transform.Position + glm::vec3(collider.Offset, 0.001f);
                    Renderer::DrawCircle(pos, transform.Rotation, transform.Scale * collider.Radius * 2.0f, m_PhysicsVisibleColor);
                }
            }
        }
        Renderer::EndScene();
    }
    void EditorLayer::NewProject()
    {
        Project::New();
    }
    bool EditorLayer::OpenProject()
    {
        std::string filepath = FileDialogs::OpenFile("Euler Project(*.kproj)\0*.kproj\0");
        if (!filepath.empty()) {
            OpenProject();
            return true;
        }
        return false;
    }
    void EditorLayer::OpenProject(const std::filesystem::path& path)
    {
        if (Project::Load(path)) {
            auto start_scene_path = Project::GetPath(Project::GetActive()->GetConfig().m_StartScene);
            KINK_CORE_WARN("SCENE LOAD: {0}", start_scene_path.string());
            OpenScene(start_scene_path);
            m_AssetBrowserPanel = CreateScope<AssetBrowserPanel>();
        }
        else {
            KINK_CORE_WARN("SCENE LOAD FAILED...");
        }
    }
    void EditorLayer::SaveProject()
    {

    }
    void EditorLayer::NewScene()
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
        m_EditingScenePath = std::filesystem::path();
    }
    void EditorLayer::OpenScene()
    {
        std::string filepath = FileDialogs::OpenFile("Kink Scene (*.kink)\0*.kink\0");
        if (!filepath.empty()) {
            OpenScene(filepath);
        }
    }
    void EditorLayer::OpenScene(const std::filesystem::path& path)
    {
        if (m_SceneState != SceneState::Edit) {
            OnSceneStop();
        }
        if (path.extension() != ".kink") {
            KINK_CORE_WARN("Could not open file. File extension is not .kink");
            return;
        }
        Ref<Scene> scene = CreateRef<Scene>();
        SceneSerializer serializer(scene);
        if (serializer.Deserialize(path.string())) {
            m_EditorScene = scene;
            //m_EditorScene->OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveScene = m_EditorScene;
            m_SceneHierarchyPanel.SetContext(m_ActiveScene);
            m_EditingScenePath = path;
        }
    }
    void EditorLayer::SaveScene()
    {
        if (m_EditingScenePath.empty()) {
            SaveSceneAs();
        }
        else {
            SceneSerializer serializer(m_ActiveScene);
            serializer.Serialize(m_EditingScenePath.string());
        }
    }
    void EditorLayer::SaveSceneAs()
    {
        std::string filepath = FileDialogs::SaveFile("Kink Scene (*.kink)\0*.kink\0");
        if (!filepath.empty()) {
            SceneSerializer serializer(m_ActiveScene);
            serializer.Serialize(filepath);
            m_EditingScenePath = filepath;
        }
    }
    
    void EditorLayer::OnSimulationPlay()
    {
        m_SceneState = SceneState::Simulate;
        m_ActiveScene = Scene::Copy(m_EditorScene);
        m_ActiveScene->OnRuntimeStart();
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }
    void EditorLayer::OnSimulationStop()
    {
        m_SceneState = SceneState::Edit;
        m_ActiveScene->OnRuntimeStop();
        m_ActiveScene = m_EditorScene;
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OnScenePlay()
    {
        if (m_SceneState == SceneState::Simulate) {
            OnSimulationStop();
        }
        m_SceneState = SceneState::Play;
        m_ActiveScene = Scene::Copy(m_EditorScene);
        m_ActiveScene->OnRuntimeStart();
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }
    void EditorLayer::OnSceneSimulate()
    {
        if (m_SceneState == SceneState::Play) {
            OnSimulationStop();
        }
        m_SceneState = SceneState::Simulate;
        m_ActiveScene = Scene::Copy(m_EditorScene);
        m_ActiveScene->OnSimulationStart();
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }
    void EditorLayer::OnSceneStop()
    {
        if (m_SceneState == SceneState::Play) {
            m_ActiveScene->OnRuntimeStop();
        }
        else if (m_SceneState == SceneState::Simulate) {
            m_ActiveScene->OnSimulationStop();
        }
        m_SceneState = SceneState::Edit;
        m_ActiveScene = m_EditorScene;
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OnScenePause()
    {
        if (m_SceneState == SceneState::Edit) {
            return;
        }
        m_ActiveScene->Pause(true);
    }

    void EditorLayer::OnDuplicateGameObject()
    {
        if (m_SceneState != SceneState::Edit) {
            return;
        }
        GameObject selectd = m_SceneHierarchyPanel.GetSelectedGameObject();
        if (selectd) {
            m_EditorScene->DuplicateObject(selectd);
        }
    }
    void EditorLayer::UI_Toolbar()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 2.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.3f, 0.0f, 0.5f));

        ImGui::Begin("##Toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
        {
            Ref<Texture2D> icon = (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate) ? m_IconPlay : m_IconStop;
            float size = ImGui::GetWindowHeight() - 5.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
            ImGui::PushID(icon->GetRendererID());
            if (ImGui::ImageButton("", (ImTextureID)icon->GetRendererID(), ImVec2(size, size * 0.85f), ImVec2(0, 0), ImVec2(1, 1))) {
                if (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Simulate) {
                    OnScenePlay();
                }
                else if (m_SceneState == SceneState::Play) {
                    OnSceneStop();
                }
            }
            ImGui::PopID();
        }
        ImGui::SameLine();
        {
            Ref<Texture2D> icon = (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Play) ? m_IconSimulate : m_IconStop;
            float size = ImGui::GetWindowHeight() - 5.0f;
            ImGui::PushID(icon->GetRendererID());
            if (ImGui::ImageButton("", (ImTextureID)icon->GetRendererID(), ImVec2(size, size * 0.85f), ImVec2(0, 0), ImVec2(1, 1))) {
                if (m_SceneState == SceneState::Edit || m_SceneState == SceneState::Play) {
                    OnSceneSimulate();
                }
                else if (m_SceneState == SceneState::Simulate) {
                    OnSceneStop();
                }
            }
            ImGui::PopID();
        }
        if (m_SceneState != SceneState::Edit) {
            bool isPaused = m_ActiveScene->IsPaused();
            ImGui::SameLine();
            {
                Ref<Texture2D> icon = m_IconPause;
                float size = ImGui::GetWindowHeight() - 5.0f;
                ImGui::PushID(icon->GetRendererID());
                if (ImGui::ImageButton("", (ImTextureID)icon->GetRendererID(), ImVec2(size, size * 0.85f), ImVec2(0, 0), ImVec2(1, 1))) {
                    m_ActiveScene->Pause(!isPaused);
                }
                ImGui::PopID();
            }
            if (isPaused) {
                ImGui::SameLine();
                {
                    Ref<Texture2D> icon = m_IconStep;
                    float size = ImGui::GetWindowHeight() - 5.0f;
                    ImGui::PushID(icon->GetRendererID());
                    if (ImGui::ImageButton("", (ImTextureID)icon->GetRendererID(), ImVec2(size, size * 0.85f), ImVec2(0, 0), ImVec2(1, 1))) {
                        m_ActiveScene->Step(1);
                    }
                    ImGui::PopID();
                }
            }
        }

        ImGui::End();
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
    }
}
