#pragma once
#include"../Math/EulerMath.h"
#include"../Render/GLObjects/GLSquare.h"
#include"../Render/OpenGL/GLSourceManager.h"
#include<vector>
#include<map>
using namespace std;
namespace EulerEngine {
	vector<glm::vec3> test_pos;
	void vegetationInit() {
		test_pos.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
		test_pos.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
		test_pos.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
		test_pos.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
		test_pos.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
	}
	void TestSquareRender(Square* square,
		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
		int dCnt, EulerDirLight* dLight,
		int sCnt, EulerSpotLight* sLight,
		int pCnt, EulerPointLight* pLight) {
		glStencilMask(0x00);
		square->setShader(SourceManager::GetInstance()->getShader("grass"));
		for (unsigned int i = 0; i < test_pos.size(); i++)
		{
			square->setTransform(test_pos[i], glm::vec3(1.0f), glm::vec3(0.0f));
			square->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
			square->Render(model, view, projection, viewPos);
		}
	}
	void TestWindowRender(Square* square,
		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
		int dCnt, EulerDirLight* dLight,
		int sCnt, EulerSpotLight* sLight,
		int pCnt, EulerPointLight* pLight) {
		glStencilMask(0x00);
		map<float, glm::vec3> sorted;
		for (auto windowPos:test_pos) {
			float instance = glm::length(viewPos - windowPos);
			sorted[instance] = windowPos;
		}

		square->setShader(SourceManager::GetInstance()->getShader("window"));
		for (map<float,glm::vec3>::reverse_iterator it = sorted.rbegin();it!=sorted.rend();it++)
		{
			square->setTransform(it->second, glm::vec3(1.0f), glm::vec3(0.0f));
			square->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
			square->Render(model, view, projection, viewPos);
		}
	}
}