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
		virtual void OnEvent(Event& event) override;
		
		void Begin();
		void End();
		void SetBlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}