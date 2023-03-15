#pragma once
#include<memory>
#include"../OpenGL/GLCamera.h"
#include"../OpenGL/GLScene.h"
#include"../GLObjects/GLLight.h"
#include"../GLObjects/GLRenderObject.h"
namespace EulerEngine {
	class Camera;
	struct ContentViewportInfo{
		float x = 0.0f;
		float y = 0.0f;
		float width = 800.0f;
		float height = 600.0f;
	};
	class RenderSystem {
	public:
		RenderSystem() = default;
		~RenderSystem() {}
		void initialize();
		void update(double deltaTime);
		void clear();

		void DataLogic2Render();
		std::shared_ptr<Camera> getRenderCamera() const;
		void updateContentViewport(float offsetX,float loffsetY,float width,float height);
		std::shared_ptr<ContentViewportInfo> getContentViewport() const;
		float getAspect() const { return m_viewport_info->width / m_viewport_info->height; }

		void addRenderObject(const std::string objName,RenderObject* object);
		RenderObject* getRenderObject(const std::string objName)const;
		void addSpotLight(EulerSpotLight* light);
		EulerSpotLight* getSpotLight()const;

	private:
		std::shared_ptr<Camera> m_render_camera;
		std::shared_ptr<Scene>m_render_scene;
		std::shared_ptr<ContentViewportInfo> m_viewport_info;
		void processSwapData();
		void gladInit();
	};
}