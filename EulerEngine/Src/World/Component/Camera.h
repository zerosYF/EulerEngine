#pragma once
#include"Render/Camera/EulerCamera.h"
namespace EulerEngine {
	struct Camera {
		Ref<EulerCamera> RendererCamera;
		bool isPrimary = true;
		bool isFixedAspectRatio = false;

		Camera() = default;
		Camera(const Camera&) = default;
		Camera(CameraType type) {
			RendererCamera = CreateRef<EulerCamera>(type);
		}
	};
}
