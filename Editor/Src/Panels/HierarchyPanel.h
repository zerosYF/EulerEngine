#pragma once
#include"GutKink.h"
namespace EulerEngine {
	class HierarchyPanel {
	public:
		HierarchyPanel() = default;
		HierarchyPanel(const Ref<Scene>& defaultScene);
		void SetContext(const Ref<Scene>& scene);
		void OnImGuiRender();
		GameObject GetSelectedGameObject() const { return m_SelectedGameObject; }
		void SetSeletedGameObject(GameObject gameObject) { m_SelectedGameObject = gameObject; }
	private:
		void DrawGameObjectNode(GameObject gameObject);
		void DrawComponents(GameObject gameObject);
		template<typename T>
		void DisplayAddComponentPopup(std::string name);
	private:
		Ref<Scene> m_Context;
		GameObject m_SelectedGameObject;
	};
}