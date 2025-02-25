#include "gkpch.h"
#include"HierarchyPanel.h"
#include <imgui_internal.h>
namespace EulerEngine {
	HierarchyPanel::HierarchyPanel(const Ref<Scene>& defaultScene):m_Context(defaultScene)
	{
	}
	void HierarchyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
	}
	void HierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");
		m_Context->m_Registry.view<Profile>().each([&](auto entity, auto& tc) {
			GameObject gameObject{ entity, m_Context.get() };
			DrawGameObjectNode(gameObject);
		});
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
			if (ImGui::MenuItem("MeshRenderer")) {
				m_SelectedGameObject.AddComponent<MeshRenderer>();
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Camera")) {
				m_SelectedGameObject.AddComponent<Camera>();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		DrawComponent<Transform>("Transform", gameObject, [](Transform& com) {
			DrawVec3Control("Position", com.Position);
			DrawVec3Control("Rotation", com.Rotation);
			DrawVec3Control("Scale", com.Scale, 1.0f);
		});
		DrawComponent<Camera>("Camera", gameObject, [](Camera& com) {
			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)com.RendererCamera->GetCameraType()];
			if (ImGui::BeginCombo("CameraType", currentProjectionTypeString)) {
				for (int i = 0; i < 2; i++) {
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
						currentProjectionTypeString = projectionTypeStrings[i];
						com.RendererCamera->SetCameraType((CameraType)i);
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			if (com.RendererCamera->GetCameraType() == CameraType::PERSPECTIVE) {
				float fov = com.RendererCamera->GetFovAngle();
				if (ImGui::DragFloat("FOV", &fov, 0.1f, 1.0f, 179.0f)) {
					com.RendererCamera->SetFovAngle(fov);
				}
				float nearClip = com.RendererCamera->GetPerspectiveNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip, 0.1f, 0.0f, com.RendererCamera->GetPerspectiveFarClip())) {
					com.RendererCamera->SetPerspectiveNearClip(nearClip);
				}
				float farClip = com.RendererCamera->GetPerspectiveFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip, 0.1f, nearClip, 10000.0f)) {
					com.RendererCamera->SetPerspectiveFarClip(farClip);
				}
			}
			else if (com.RendererCamera->GetCameraType() == CameraType::ORTHOGRAPHIC) {
				float level = com.RendererCamera->GetZoomLevel();
				if (ImGui::DragFloat("Level", &level, 0.1f, 0.0f, 1000.0f)) {
					com.RendererCamera->SetZoomLevel(level);
				}
				float nearClip = com.RendererCamera->GetOrthographicNearClip();
				if (ImGui::DragFloat("Near Clip", &nearClip, 0.1f, 0.0f, com.RendererCamera->GetOrthographicFarClip())) {
					com.RendererCamera->SetOrthographicNearClip(nearClip);
				}
				float farClip = com.RendererCamera->GetOrthographicFarClip();
				if (ImGui::DragFloat("Far Clip", &farClip, 0.1f, nearClip, 10000.0f)) {
					com.RendererCamera->SetOrthographicFarClip(farClip);
				}
			}
		});
		DrawComponent<MeshRenderer>("MeshRenderer", gameObject, [](MeshRenderer& com) {
			ImGui::ColorEdit4("Color", &com.Material->GetColor()[0]);
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