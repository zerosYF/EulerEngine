#pragma once
#include"../Render/GLObjects/GLCube.h"
#include"../Render/OpenGL/GLSourceManager.h"
namespace EulerEngine {
	void TestStencilInit() {
		SourceManager::GetInstance()->loadShader("stencil", "Shaders/Stencil/Stencil.vert", "Shaders/Stencil/Stencil.frag");
	}
	void TestStencilRender(Cube cube,
		glm::mat4 model,glm::mat4 view,glm::mat4 projection,glm::vec3 viewPos,
		int dCnt, EulerDirLight* dLight,
		int sCnt, EulerSpotLight* sLight,
		int pCnt, EulerPointLight* pLight) {

		glStencilFunc(GL_ALWAYS, 1, 0xff);
		glStencilMask(0xff);
		cube.setShader(SourceManager::GetInstance()->getShader("universal"));
		cube.setTransform(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
		cube.setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
		cube.Render(model, view, projection, viewPos);

		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		cube.setShader(SourceManager::GetInstance()->getShader("stencil"));
		cube.setTransform(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.1f), glm::vec3(0.0f));
		cube.Render(model, view, projection, viewPos);
		glStencilMask(0xff);
		glEnable(GL_DEPTH_TEST);
	}
}