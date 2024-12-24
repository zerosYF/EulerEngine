#include "gkpch.h"
#include "EulerLayerStack.h"
namespace EulerEngine {
	EulerLayerStack::EulerLayerStack() {
	}
	EulerLayerStack::~EulerLayerStack() {
		for (EulerLayer* layer: m_Layers) {
			layer->OnDetach();
			delete layer;
		}
	}
	void EulerLayerStack::PushLayer(EulerLayer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}
	void EulerLayerStack::PushOverlay(EulerLayer* overlay) {
		//原地构造，提升性能
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}
	bool EulerLayerStack::PopLayer(EulerLayer* layer) {
		auto it = std::find(m_Layers.begin(),m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
			return true;
		}
		return false;
	}
	bool EulerLayerStack::PopOverlay(EulerLayer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(it);
			return true;
		}
		return false;
	}
}
