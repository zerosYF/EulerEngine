#pragma once
#include "../Core/Layer/EulerLayer.h"
#include "../Core/Events/InputEvent.h"
#include "../Core/Events/ApplicationEvent.h"
namespace EulerEngine {
	class KINK_API ImGuiLayer :public EulerLayer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}