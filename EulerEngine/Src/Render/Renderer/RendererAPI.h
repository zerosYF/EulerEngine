#pragma once
#include"gkpch.h"
#include<glm/glm.hpp>
#include"Render/VertexArray.h"
namespace EulerEngine {
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			DirectX = 2
		};
	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray, unsigned int vertex_cnt) = 0;
		inline static API getAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}