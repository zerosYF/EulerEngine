#pragma once
#include"Render/Camera/EulerCamera.h"
namespace EulerEngine {
	struct CameraComponent {
		Ref<EulerCamera> Camera;
		CameraType type{ PERSPECTIVE };
		bool isPrimary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(CameraType type): type(type) {
			Camera = EulerCamera::Create(type);
		}
	};
}
