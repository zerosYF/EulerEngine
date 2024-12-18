#include "gkpch.h"
#include"EulerContext.h"
#include"../../Test/TestFunc.h"
#include<memory>
namespace EulerEngine {
	/*RuntimeGlobalContext g_global_context;
	void RuntimeGlobalContext::startSystems() {
		m_window_system = std::make_shared<WindowSystem>();
		WindowInfo info;
		m_window_system->Initialize(info);
		m_timer_system = std::make_shared<TimerSystem>();
		m_timer_system->Initialize();
		m_input_system = std::make_shared<InputSystem>();
		m_input_system->initialize();
		m_render_system = std::make_shared<RenderSystem>();
		m_render_system->initialize();

		m_source_mgr = std::make_shared<SourceManager>();
		m_source_mgr->Initialize();
	}
	void RuntimeGlobalContext::initObject() {
		m_source_mgr->loadShader("universal", "Shaders/Light/common.vert", "Shaders/Light/common.frag");
		m_source_mgr->loadShader("grass", "Shaders/Blend/Blend.vert", "Shaders/Blend/Blend.frag");
		m_source_mgr->loadShader("window", "Shaders/Blend/Blend.vert", "Shaders/Blend/Window.frag");
		m_source_mgr->loadShader("stencil", "Shaders/Stencil/Stencil.vert", "Shaders/Stencil/Stencil.frag");
		m_source_mgr->loadTexture("Assets/mytextures/container2.png", "wood");
		m_source_mgr->loadTexture("Assets/mytextures/container2_specular.png", "container");
		m_source_mgr->loadTexture("Assets/mytextures/window.png", "window");
		
		Cube* cube = new Cube(vertices);
		m_render_system->addRenderObject("cube", cube);
		cube->addTexture(m_source_mgr->getTexture("wood"), DIFFUSE);
		cube->addTexture(m_source_mgr->getTexture("container"), SPECULAR);

		Square* square = new Square(SquareVertices);
		m_render_system->addRenderObject("square", square);
		square->addTexture(m_source_mgr->getTexture("window"), DIFFUSE);
		test_class.vegetationInit();

		EulerSpotLight* light3 = new EulerSpotLight();
		m_render_system->addSpotLight(light3);
		Shader lightShader3 = m_source_mgr->loadShader("light3", "Shaders/Light/light.vert", "Shaders/Light/light.frag");
		light3->setShader(lightShader3);
	}
	void RuntimeGlobalContext::shutdownSystems() {

	}*/
}