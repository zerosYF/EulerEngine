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
	private:
		void DrawGameObjectNode(GameObject gameObject);
		void DrawComponents(GameObject gameObject);
	private:
		Ref<Scene> m_Context;
		GameObject m_SelectedGameObject;
	};
}