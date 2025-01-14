#include "gkpch.h"
#include "RenderCmd.h"
#include "Platform/OpenGL/GLRendererAPI.h"
namespace EulerEngine {
	RendererAPI* RenderCommand::m_RendererAPI = new GLRendererAPI;
}