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
		m_Context->m_Registry.view<Profile>().each([=](auto entity, auto& tc) {
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

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f) {

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
		if (gameObject.HasComponent<Transform>()) {
			
			if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
				auto& com = gameObject.GetComponent<Transform>();
				DrawVec3Control("Position", com.Position);
				DrawVec3Control("Rotation", com.Rotation);
				DrawVec3Control("Scale", com.Scale, 1.0f);
				ImGui::TreePop();
			}
		}
		if (gameObject.HasComponent<Camera>()) {

			if (ImGui::TreeNodeEx((void*)typeid(Camera).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")) {
				auto& com = gameObject.GetComponent<Camera>();
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
				ImGui::TreePop();
			}
		}
		if (gameObject.HasComponent<MeshRenderer>()) {
			if (ImGui::TreeNodeEx((void*)typeid(MeshRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "MeshRenderer")) {
				auto& com = gameObject.GetComponent<MeshRenderer>();
				ImGui::ColorEdit4("Color", &com.Material->GetColor()[0]);
				ImGui::TreePop();
			}
		}
	}
	void HierarchyPanel::DrawGameObjectNode(GameObject gameObject)
	{
		auto& tc = gameObject.GetComponent<Profile>();
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