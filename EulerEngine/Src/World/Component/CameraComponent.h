#pragma once
#include"Render/Camera/EulerCamera.h"
namespace EulerEngine {
	struct CameraComponent {
		Ref<EulerCamera> Camera;
		bool isPrimary = true;
		bool isFixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(CameraType type) {
			Camera = CreateRef<EulerCamera>(type);
		}
	};
}
