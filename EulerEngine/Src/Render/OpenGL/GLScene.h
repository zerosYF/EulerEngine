#pragma once
#include"../GLObjects/GLLight.h"
#include"../GLObjects/GLRenderObject.h"
#include<map>
#include<memory>
namespace EulerEngine {
	class Scene {
	public:
		EulerDirLight* m_dirLight;
		EulerSpotLight* m_spotLight;
		EulerPointLight* m_pointLight;

		std::map<const std::string,RenderObject*> m_renderObjects;
		std::shared_ptr<RenderObject> m_renderAxis;
	public:
		Scene() {}
		~Scene() {}
		void clear();
		void updateVisibleObjects();
	};
}
