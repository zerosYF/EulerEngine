#include "gkpch.h"
#include "EulerLayerStack.h"
namespace EulerEngine {
	EulerLayerStack::EulerLayerStack() {
		m_LayerInsert = m_Layers.begin();
	}
	EulerLayerStack::~EulerLayerStack() {
		for (EulerLayer* layer: m_Layers) {
			delete layer;
		}
	}
	void EulerLayerStack::PushLayer(EulerLayer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}
	void EulerLayerStack::PushOverlay(EulerLayer* overlay) {
		//原地构造，提升性能
		m_Layers.emplace_back(overlay);
	}
	bool EulerLayerStack::PopLayer(EulerLayer* layer) {
		auto it = std::find(m_Layers.begin(),m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
			return true;
		}
		return false;
	}
	bool EulerLayerStack::PopOverlay(EulerLayer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			return true;
		}
		return false;
	}
}
