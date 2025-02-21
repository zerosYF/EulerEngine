#include "gkpch.h"
#include"HierarchyPanel.h"
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
		m_Context->m_Registry.view<TagComponent>().each([=](auto entity, auto& tc) {
			GameObject gameObject{ entity, m_Context.get() };
			DrawGameObjectNode(gameObject);
		});
		if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()) {
			m_SelectedGameObject = {};
		}
		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectedGameObject) {
			DrawComponents(m_SelectedGameObject);
		}
		ImGui::End();

	}
	void HierarchyPanel::DrawComponents(GameObject gameObject)
	{
		if (gameObject.HasComponent<TagComponent>()) {
			auto& tag = gameObject.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
				tag = std::string(buffer);
			}
		}
		if (gameObject.HasComponent<TransformComponent>()) {
			
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
				auto& com = gameObject.GetComponent<TransformComponent>();
				ImGui::DragFloat3("Position", &com.Position[0], 0.1f);
				ImGui::DragFloat3("Rotation", &com.Rotation[0], 0.1f);
				ImGui::DragFloat3("Scale", &com.Scale[0], 0.1f);
				ImGui::TreePop();
			}
		}
		if (gameObject.HasComponent<CameraComponent>()) {

			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")) {
				auto& com = gameObject.GetComponent<CameraComponent>();
				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)com.Camera->GetCameraType()];
				if (ImGui::BeginCombo("CameraType", currentProjectionTypeString)) {
					for (int i = 0; i < 2; i++) {
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
							currentProjectionTypeString = projectionTypeStrings[i];
							com.Camera->SetCameraType((CameraType)i);
						}
						if (isSelected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}
				if (com.Camera->GetCameraType() == CameraType::PERSPECTIVE) {
					float fov = com.Camera->GetFovAngle();
					if (ImGui::DragFloat("FOV", &fov, 0.1f, 1.0f, 179.0f)) {
						com.Camera->SetFovAngle(fov);
					}
					float nearClip = com.Camera->GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near Clip", &nearClip, 0.1f, 0.0f, com.Camera->GetPerspectiveFarClip())) {
						com.Camera->SetPerspectiveNearClip(nearClip);
					}
					float farClip = com.Camera->GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far Clip", &farClip, 0.1f, nearClip, 10000.0f)) {
						com.Camera->SetPerspectiveFarClip(farClip);
					}
				}
				else if (com.Camera->GetCameraType() == CameraType::ORTHOGRAPHIC) {
					float level = com.Camera->GetZoomLevel();
					if (ImGui::DragFloat("Level", &level, 0.1f, 0.0f, 1000.0f)) {
						com.Camera->SetZoomLevel(level);
					}
					float nearClip = com.Camera->GetOrthographicNearClip();
					if (ImGui::DragFloat("Near Clip", &nearClip, 0.1f, 0.0f, com.Camera->GetOrthographicFarClip())) {
						com.Camera->SetOrthographicNearClip(nearClip);
					}
					float farClip = com.Camera->GetOrthographicFarClip();
					if (ImGui::DragFloat("Far Clip", &farClip, 0.1f, nearClip, 10000.0f)) {
						com.Camera->SetOrthographicFarClip(farClip);
					}
				}
				ImGui::TreePop();
			}
		}
	}
	void HierarchyPanel::DrawGameObjectNode(GameObject gameObject)
	{
		auto& tc = gameObject.GetComponent<TagComponent>();   
		ImGuiTreeNodeFlags flags = ( (m_SelectedGameObject == gameObject) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool isOpen = ImGui::TreeNodeEx((void*)(unsigned int)gameObject, flags, tc.Tag.c_str());
		if (ImGui::IsItemClicked()) {
			m_SelectedGameObject = gameObject;
		}
		if (isOpen) {
			ImGui::TreePop();
		}
	}
}