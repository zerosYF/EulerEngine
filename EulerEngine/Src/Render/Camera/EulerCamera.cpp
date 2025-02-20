#include"gkpch.h"
#include"EulerCamera.h"
#include"PerspectiveCamera.h"
#include"OrthoCamera.h"
namespace EulerEngine {
	Ref<EulerCamera> EulerCamera::Create(CameraType type)
	{
		switch (type) {
		case PERSPECTIVE:
			return CreateRef<PerspectiveCamera>();
		case ORTHOGRAPHIC:
			return CreateRef<OrthoCamera>();
		}
		return nullptr;
	}
}