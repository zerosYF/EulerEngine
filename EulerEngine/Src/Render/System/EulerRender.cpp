#include"EulerRender.h"
#include"../../Game/Context/EulerContext.h"
#include"../../Math/EulerMath.h"
#include"../../Test/TestFunc.h"
namespace EulerEngine {
	void ProcessKeyboard(Camera_Movement direction) {
		std::shared_ptr<Camera> camera = g_global_context.m_render_system->getRenderCamera();
		float vel = camera->m_movementSpeed * (g_global_context.m_timer_system->GetDeltaTime());
		if (direction == FORWARD) {
			camera->m_position += camera->m_front * vel;
		}
		if (direction == BACKWARD) {
			camera->m_position -= camera->m_front * vel;
		}
		if (direction == LEFT) {
			camera->m_position -= camera->m_right * vel;
		}
		if (direction == RIGHT) {
			camera->m_position += camera->m_right * vel;
		}
	}
	void TestKeyFunc(int key, int scanCode, int action, int mode) {
		if (key == GLFW_KEY_W) {
			ProcessKeyboard(FORWARD);
		}
		if (key == GLFW_KEY_S) {
			ProcessKeyboard(BACKWARD);
		}
	}
	void RenderSystem::initialize() {
		gladInit();
		m_render_camera = std::make_shared<Camera>();
		m_viewport_info = std::make_shared<ContentViewportInfo>();
		m_render_scene = std::make_shared<Scene>();
		g_global_context.m_window_system->registerKeyFunc(TestKeyFunc);
	}

	glm::vec3 plantPosition(0.0f, 0.0f, 0.0f);
	void RenderSystem::update(double deltaTime) {
		//ProcessInput(g_global_context.m_window_system->getWindow(), m_render_camera);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		float aspect = getAspect();
		glm::mat4 projection =
			glm::perspective(glm::radians(m_render_camera->m_fovAngle), aspect, 0.1f, 100.0f);
		glm::mat4 view = m_render_camera->GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		EulerSpotLight* light3 = (EulerSpotLight*)getSpotLight();
		light3->setTransform(m_render_camera->m_position, glm::vec3(0.1f), glm::vec3(0.0f));
		light3->setDirection(m_render_camera->m_front);
		light3->Render(model, view, projection);

		Cube* cube = (Cube*)getRenderObject("cube");
		Shader shaderUni = g_global_context.m_source_mgr->getShader("universal");
		Shader shaderSten = g_global_context.m_source_mgr->getShader("stencil");
		test_class.TestPlantRender(cube, model, view, projection, m_render_camera->m_position, 0, nullptr, 1, light3, 0, nullptr,shaderUni);
		test_class.TestCubeRender(cube, model, view, projection, m_render_camera->m_position, 0, nullptr, 1, light3, 0, nullptr,shaderUni);

		glfwSwapBuffers(g_global_context.m_window_system->getWindow());
		glfwPollEvents();
	}
	void RenderSystem::clear() {
	}
	void RenderSystem::DataLogic2Render() {
	}
	std::shared_ptr<Camera> RenderSystem::getRenderCamera() const{
		return m_render_camera;
	}
	void RenderSystem::updateContentViewport(float offsetX, float loffsetY, float width, float height) {

	}
	std::shared_ptr<ContentViewportInfo> RenderSystem::getContentViewport() const {
		return m_viewport_info;
	}
	void RenderSystem::addRenderObject(const std::string objName,RenderObject* object) {
		m_render_scene->m_renderObjects[objName] = object;
	}
	RenderObject* RenderSystem::getRenderObject(const std::string objName) const{
		return m_render_scene->m_renderObjects[objName]; 
	}
	void RenderSystem::addSpotLight(EulerSpotLight* light) {
		m_render_scene->m_spotLight = light;
	}
	EulerSpotLight* RenderSystem::getSpotLight() const{ 
		return m_render_scene->m_spotLight; 
	}
	void RenderSystem::gladInit() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			cout << "failed to init GLAD" << endl;
		}
	}
}