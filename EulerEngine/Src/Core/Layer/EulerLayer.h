#pragma once
#include "GutKink/Core.h"
#include "Core/Events/Event.h"
namespace EulerEngine {
	class KINK_API EulerLayer
	{
	public:
		EulerLayer() = default;
		EulerLayer(const std::string& name = "Layer") :m_Name(name) {

		}
		virtual ~EulerLayer() = default;

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

