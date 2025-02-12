#pragma once
#include"OrthoCamera.h"
#include"Resource/ResourceLibrary.h"
namespace EulerEngine {
	class Renderer2D {
	public:  
		static void Init();
		static void ShutDown();
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};
}