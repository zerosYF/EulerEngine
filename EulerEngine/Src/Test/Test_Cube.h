#pragma once
#include"../Render/GLObjects/GLCube.h"
#include"../Render/OpenGL/GLSourceManager.h"
namespace EulerEngine {
	void TestCubeRender(Cube* cube,
		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
		int dCnt, EulerDirLight* dLight,
		int sCnt, EulerSpotLight* sLight,
		int pCnt, EulerPointLight* pLight) {
		glStencilMask(0x00);
		cube->setShader(SourceManager::GetInstance()->getShader("universal"));
		cube->setTransform(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
		cube->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
		cube->Render(model, view, projection, viewPos);
	}
	void TestPlantRender(Cube* cube,
		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
		int dCnt, EulerDirLight* dLight,
		int sCnt, EulerSpotLight* sLight,
		int pCnt, EulerPointLight* pLight) {
		glStencilMask(0x00);
		cube->setShader(SourceManager::GetInstance()->getShader("universal"));
		cube->setTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 0.5f, 5.0f), glm::vec3(0.0f));
		cube->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
		cube->Render(model, view, projection, viewPos);
	}
}
