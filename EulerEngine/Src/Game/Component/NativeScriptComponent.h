#pragma once
#include"glm/glm.hpp"
#include"Core/EulerTimer.h"
namespace EulerEngine {
	// Forward declaration
	class EulerBehaviour;
	struct NativeScriptComponent {
		EulerBehaviour* Instance = nullptr;
		EulerBehaviour*(*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);
		template<typename T>
		void Bind() {
			InstantiateScript = []() { return static_cast<EulerBehaviour*>(new T()); };
			DestroyScript = [](NativeScriptComponent* component) { delete component->Instance; component->Instance = nullptr; };
		}
	};
}
