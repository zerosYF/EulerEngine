#pragma once
#include "../Core/Layer/EulerLayer.h"
namespace EulerEngine {
	class KINK_API ImGuiLayer :public EulerLayer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private:
		float m_Time = 0.0f;
	};
}