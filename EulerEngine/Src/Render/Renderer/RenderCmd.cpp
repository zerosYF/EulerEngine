#include "gkpch.h"
#include "RenderCmd.h"
#include "Platform/OpenGL/GLRendererAPI.h"
namespace EulerEngine {
	Scope<RendererAPI> RenderCommand::m_RendererAPI = RendererAPI::Create();
}