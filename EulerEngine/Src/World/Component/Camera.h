#pragma once
#include"Render/Camera/EulerCamera.h"
namespace EulerEngine {
	struct Camera {
		EulerCamera RendererCamera;
		bool isPrimary = true;
		bool isFixedAspectRatio = false;

		Camera() = default;
		Camera(const Camera&) = default;
	};
}
