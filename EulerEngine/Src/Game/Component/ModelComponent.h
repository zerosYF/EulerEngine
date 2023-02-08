#pragma once
#include"ComponentBase.h"
#include"../../Render/GLObjects/GLRenderObject.h"
using namespace std;
class ModelComponent :ComponentBase{
	EulerEngine::RenderObject renderObject;
	void tick();
};