#pragma once
#include"Core.h"
#include"EulerLayer.h"
#include<vector>
namespace EulerEngine {
	class EulerLayerStack
	{
	public:
		EulerLayerStack() = default;
		~EulerLayerStack();

		void PushLayer(EulerLayer* layer);
		void PushOverlay(EulerLayer* overlay);
		bool PopLayer(EulerLayer* layer);
		bool PopOverlay(EulerLayer* overlay);

		std::vector<EulerLayer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<EulerLayer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<EulerLayer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}

