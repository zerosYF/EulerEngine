#pragma once
#include"ComponentBase.h"
#include"../../Render/GLObjects/GLRenderObject.h"
class ModelComponent {
	EulerEngine::RenderObject renderObject;
	void tick();
};