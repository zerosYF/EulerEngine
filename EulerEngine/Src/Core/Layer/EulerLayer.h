#pragma once
#include "../../GutKink/Core.h"
#include "../Events/Event.h"
namespace EulerEngine {
	class KINK_API EulerLayer
	{
	public:
		EulerLayer(const std::string& name = "Layer");
		virtual ~EulerLayer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	};
}

