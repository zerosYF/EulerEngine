#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	// Forward declaration
	class EulerBehaviour;
	struct NativeScript {
		EulerBehaviour* Instance = nullptr;
		EulerBehaviour*(*InstantiateScript)();
		void (*DestroyScript)(NativeScript*);
		template<typename T>
		void Bind() {
			InstantiateScript = []() { return static_cast<EulerBehaviour*>(new T()); };
			DestroyScript = [](NativeScript* component) { delete component->Instance; component->Instance = nullptr; };
		}
	};
}
