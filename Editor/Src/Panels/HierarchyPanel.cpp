#include"gkpch.h"
#include"HierarchyPanel.h"
#include<imgui_internal.h>
#include<filesystem>
namespace EulerEngine {
	extern const std::filesystem::path g_AssetsPath;
	HierarchyPanel::HierarchyPanel(const Ref<Scene>& defaultScene):m_Context(defaultScene)
	{
	}
	void HierarchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
		m_SelectedGameObject = {};
	}
	void HierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");
		if (m_Context) {
			auto view = m_Context->m_Registry.view<IDCom>();
			for (auto entity : view) {
				auto& id_com = view.get<IDCom>(entity);
				GameObject gameObject{ entity, m_Context.get() };
				DrawGameObjectNode(gameObject);
			}
			if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()) {
				m_SelectedGameObject = {};
			}
			// right-click on empty space to create new object
			ImGuiPopupFlags flags = ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonRight;
			if (ImGui::BeginPopupContextWindow(0, flags)) {
				if (ImGui::MenuItem("Create EmptyObject")) {
					m_Context->CreateObject("GameObject");
				}
				ImGui::EndPopup();
			}
		}
		ImGui::End();
		ImGui::Begin("Properties");
		if (m_SelectedGameObject) {
			DrawComponents(m_SelectedGameObject);
		}
		ImGui::End();

	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)  {

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		if (ImGui::Button("X", buttonSize)) { values.x = resetValue; } ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button("Y", buttonSize)) { values.y = resetValue; } ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button("Z", buttonSize)) { values.z = resetValue; } ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}
	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, GameObject& gameObject, UIFunction uiFunction) {
		if (!gameObject.HasComponent<T>()) {
			return;
		}
		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanAvailWidth;
		auto& component = gameObject.GetComponent<T>();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		bool isOpen = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str());
		ImGui::SameLine(ImGui::GetWindowWidth() - 30.0f);
		if (ImGui::Button("+")) {
			ImGui::OpenPopup("ComponentSettings");

		}
		ImGui::PopStyleVar();


		bool removeComponent = false;
		if (ImGui::BeginPopup("ComponentSettings")) {
			if (ImGui::MenuItem("Remove Component")) {
				removeComponent = true;
			}
			ImGui::EndPopup();
		}
		if (isOpen) {
			uiFunction(component);
			ImGui::TreePop();
		}
		if (removeComponent) {
			gameObject.RemoveComponent<T>();
		}
	}
	template<typename T>
	void HierarchyPanel::DisplayAddComponentPopup(std::string name) {
		if (!m_SelectedGameObject.HasComponent<T>()) {
			if (ImGui::MenuItem(name.c_str())) {
				m_SelectedGameObject.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}
	void HierarchyPanel::DrawComponents(GameObject gameObject)
	{
		if (gameObject.HasComponent<Profile>()) {
			auto& tag = gameObject.GetComponent<Profile>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
				tag = std::string(buffer);
			}
		}
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::Button("Add Component")) {
			ImGui::OpenPopup("AddComponent");
		}
		if (ImGui::BeginPopup("AddComponent")) {
			DisplayAddComponentPopup<MeshRenderer>("MeshRenderer");
			DisplayAddComponentPopup<Camera>("Camera");
			DisplayAddComponentPopup<SpriteRenderer>("SpriteRenderer");
			DisplayAddComponentPopup<Rigidbody2D>("Rigidbody2D");
			DisplayAddComponentPopup<BoxCollider2D>("BoxCollider2D");
			DisplayAddComponentPopup<CircleRenderer>("CirlceRenderer");
			DisplayAddComponentPopup<CircleCollider2D>("CircleCollider2D");
			DisplayAddComponentPopup<CSharpScript>("CSharpScript");
			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		DrawComponent<Transform>("Transform", gameObject, [](Transform& com) {
			DrawVec3Control("Position", com.Position);
			glm::vec3 rotation = glm::degrees(com.Rotation);
			DrawVec3Control("Rotation", rotation);
			com.Rotation = glm::radians(rotation);
			DrawVec3Control("Scale", com.Scale, 1.0f);
		});
		DrawComponent<Camera>("Camera", gameObject, [](Camera& com) {
			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)com.RendererCamera.GetCameraType()];
			if (ImGui::BeginCombo("CameraType", currentProjectionTypeString)) {
				for (int i = 0; i < 2; i++) {
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
						currentProjectionTypeString = projectionTypeStrings[i];
						com.RendererCamera.SetCameraType((CameraType)i);
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			if (com.RendererCamera.GetCameraType() == CameraType::PERSPECTIVE) {
				float fov = com.RendererCamera.GetFovAngle();
				if (ImGui::DragFloat("FOV", &fov, 0.1f, 1.0f, 179.0f)) {
					com.RendererCamera.SetFovAngle(fov);
				}
				float nearClip = com.RendererCamera.GetPerspectiveNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip, 0.1f, 0.0f, com.RendererCamera.GetPerspectiveFarClip())) {
					com.RendererCamera.SetPerspectiveNearClip(nearClip);
				}
				float farClip = com.RendererCamera.GetPerspectiveFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip, 0.1f, nearClip, 10000.0f)) {
					com.RendererCamera.SetPerspectiveFarClip(farClip);
				}
			}
			else if (com.RendererCamera.GetCameraType() == CameraType::ORTHOGRAPHIC) {
				float level = com.RendererCamera.GetZoomLevel();
				if (ImGui::DragFloat("Level", &level, 0.1f, 0.0f, 1000.0f)) {
					com.RendererCamera.SetZoomLevel(level);
				}
				float nearClip = com.RendererCamera.GetOrthographicNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip, 0.1f, 0.0f, com.RendererCamera.GetOrthographicFarClip())) {
					com.RendererCamera.SetOrthographicNearClip(nearClip);
				}
				float farClip = com.RendererCamera.GetOrthographicFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip, 0.1f, nearClip, 10000.0f)) {
					com.RendererCamera.SetOrthographicFarClip(farClip);
				}
			}
		});
		DrawComponent<MeshRenderer>("MeshRenderer", gameObject, [](MeshRenderer& com) {
			ImGui::ColorEdit4("Color", &com.Material->GetColor()[0]);
			ImGui::Button("Texture", ImVec2{ 100, 0 });
			if(ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetBrowserItem")) {
					const wchar_t* path = (const wchar_t*)payload->Data;
					std::filesystem::path texturePath = std::filesystem::path(g_AssetsPath) / path;
					com.Material->SetTexture(Texture2D::Create(texturePath.string()));
				}
				ImGui::EndDragDropTarget();
			}
		});
		DrawComponent<SpriteRenderer>("SpriteRenderer", gameObject, [](SpriteRenderer& com) {
			ImGui::ColorEdit4("Color", &com.Material->GetColor()[0]);
			ImGui::Button("Texture", ImVec2{ 100, 0 });
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetBrowserItem")) {
					const wchar_t* path = (const wchar_t*)payload->Data;
					std::filesystem::path texturePath = std::filesystem::path(g_AssetsPath) / path;
					com.Material->SetTexture(Texture2D::Create(texturePath.string()));
				}
				ImGui::EndDragDropTarget();
			}
		});
		DrawComponent<Rigidbody2D>("Rigidbody2D", gameObject, [](Rigidbody2D& com) {
			const char* type[] = {"Static", "Dynamic", "Kinematic" };
			const char* currentTypeString = type[(int)com.Type];
			if (ImGui::BeginCombo("Type", currentTypeString)) {
				for (int i = 0; i < 2; i++) {
					bool isSelected = currentTypeString == type[i];
					if (ImGui::Selectable(type[i], isSelected)) {
						currentTypeString = type[i];
						com.Type = (Rigidbody2D::BodyType)i;
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}

			ImGui::Checkbox("Fixed Rotation", &com.FixedRotation);
			ImGui::DragFloat("Mass", &com.Mass, 0.1f, 0.0f, 1000.0f);
			ImGui::DragFloat("Linear Damping", &com.LinearDamping, 0.1f, -1000.0f, 1000.0f);
			ImGui::DragFloat("Angular Damping", &com.AngularDamping, 0.1f, -1000.0f, 1000.0f);
		});
		DrawComponent<BoxCollider2D>("BoxCollider2D", gameObject, [](BoxCollider2D& com) {
			ImGui::DragFloat2("Size", glm::value_ptr(com.Size));
			ImGui::DragFloat2("Offset", glm::value_ptr(com.Offset));
			ImGui::Checkbox("Is Trigger", &com.IsTrigger);
			ImGui::DragFloat("Density", &com.Density, 0.1f, 0.0f, 1.0f);
			ImGui::DragFloat("Friction", &com.Friction, 0.1f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution", &com.Restitution, 0.1f, 0.0f, 1.0f);
		});
		DrawComponent<CircleRenderer>("CircleRenderer", gameObject, [](CircleRenderer& com) {
			ImGui::ColorEdit4("Color", &com.Color[0]);
			ImGui::DragFloat("Thickness", &com.Thickness, 0.1f, 0.0f, 1000.0f);
			ImGui::DragFloat("Fade", &com.Fade, 0.0025f, 0.0f, 1.0f);
		});
		DrawComponent<CircleCollider2D>("CircleCollider2D", gameObject, [](CircleCollider2D& com) {
			ImGui::DragFloat2("Offset", glm::value_ptr(com.Offset));
			ImGui::DragFloat("Radius", &com.Radius, 0.1f, 0.0f, 1000.0f);
			ImGui::Checkbox("Is Trigger", &com.IsTrigger);
			ImGui::DragFloat("Density", &com.Density, 0.1f, 0.0f, 1.0f);
			ImGui::DragFloat("Friction", &com.Friction, 0.1f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution", &com.Restitution, 0.1f, 0.0f, 1.0f);
		});
		DrawComponent<CSharpScript>("CSharpScript", gameObject, [](CSharpScript& com) {
			const auto& clses = ScriptEngine::GetGameObjectClasses();
			bool isExists = ScriptEngine::IsClassExists(com.Name);
			static char buffer[256];
			strcpy(buffer, com.Name.c_str());
			if (!isExists) {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
			}
			if (ImGui::InputText("Class", buffer, sizeof(buffer))) {
				com.Name = std::string(buffer);
			}
			if (!isExists) {
				ImGui::PopStyleColor();
			}
		});
	}
	void HierarchyPanel::DrawGameObjectNode(GameObject gameObject)
	{
		auto& tc = gameObject.GetComponent<Profile>();
		ImGuiTreeNodeFlags flags = ( (m_SelectedGameObject == gameObject) ? ImGuiTreeNodeFlags_Selected : 0);
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
		bool isOpen = ImGui::TreeNodeEx((void*)(unsigned int)gameObject, flags, tc.Tag.c_str());
		if (ImGui::IsItemClicked()) {
			m_SelectedGameObject = gameObject;
		}
		bool objectDeleted = false;
		if (ImGui::BeginPopupContextItem()) {
			if (ImGui::MenuItem("Delete")) {
				objectDeleted = true;
			}
			ImGui::EndPopup();
		}

		if (isOpen) {
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool isOpen = ImGui::TreeNodeEx((void*)(unsigned int)gameObject, flags, tc.Tag.c_str());
			if (isOpen) {
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		if (objectDeleted) {
			if (m_SelectedGameObject == gameObject) {
				m_SelectedGameObject = {};
			}
			m_Context->DestroyObject(gameObject);
		}
	}
}