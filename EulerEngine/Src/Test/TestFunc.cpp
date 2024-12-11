//#include"TestFunc.h"
//namespace EulerEngine {
//	TestClass test_class;
//	std::vector<glm::vec3> test_pos;
//	void TestClass::vegetationInit() {
//		test_pos.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
//		test_pos.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
//		test_pos.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
//		test_pos.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
//		test_pos.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
//	}
//	void TestClass::TestSquareRender(Square* square,
//		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
//		int dCnt, EulerDirLight* dLight,
//		int sCnt, EulerSpotLight* sLight,
//		int pCnt, EulerPointLight* pLight,
//		Shader shaderGrs) {
//		glStencilMask(0x00);
//		square->setShader(shaderGrs);
//		for (unsigned int i = 0; i < test_pos.size(); i++)
//		{
//			square->setTransform(test_pos[i], glm::vec3(1.0f), glm::vec3(0.0f));
//			square->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
//			square->Render(model, view, projection, viewPos);
//		}
//	}
//	void TestClass::TestWindowRender(Square* square,
//		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
//		int dCnt, EulerDirLight* dLight,
//		int sCnt, EulerSpotLight* sLight,
//		int pCnt, EulerPointLight* pLight,
//		Shader shaderWin) {
//		glStencilMask(0x00);
//		std::map<float, glm::vec3> sorted;
//		for (auto windowPos : test_pos) {
//			float instance = glm::length(viewPos - windowPos);
//			sorted[instance] = windowPos;
//		}
//
//		square->setShader(shaderWin);
//		for (auto it = sorted.rbegin(); it != sorted.rend(); it++)
//		{
//			square->setTransform(it->second, glm::vec3(1.0f), glm::vec3(0.0f));
//			square->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
//			square->Render(model, view, projection, viewPos);
//		}
//	}
//	void TestClass::TestStencilRender(Cube* cube,
//		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
//		int dCnt, EulerDirLight* dLight,
//		int sCnt, EulerSpotLight* sLight,
//		int pCnt, EulerPointLight* pLight,
//		Shader shaderUni, Shader shaderStencil) {
//
//		glStencilFunc(GL_ALWAYS, 1, 0xff);
//		glStencilMask(0xff);
//		cube->setShader(shaderUni);
//		cube->setTransform(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
//		cube->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
//		cube->Render(model, view, projection, viewPos);
//
//		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
//		glStencilMask(0x00);
//		glDisable(GL_DEPTH_TEST);
//		cube->setShader(shaderStencil);
//		cube->setTransform(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.1f), glm::vec3(0.0f));
//		cube->Render(model, view, projection, viewPos);
//		glStencilMask(0xff);
//		glEnable(GL_DEPTH_TEST);
//	}
//	void TestClass::TestCubeRender(Cube* cube,
//		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
//		int dCnt, EulerDirLight* dLight,
//		int sCnt, EulerSpotLight* sLight,
//		int pCnt, EulerPointLight* pLight,
//		Shader shaderUni) {
//		glStencilMask(0x00);
//		cube->setShader(shaderUni);
//		cube->setTransform(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
//		cube->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
//		glEnable(GL_CULL_FACE);
//		glCullFace(GL_BACK);
//		glFrontFace(GL_CCW);
//		cube->Render(model, view, projection, viewPos);
//		glDisable(GL_CULL_FACE);
//	}
//	void TestClass::TestPlantRender(Cube* cube,
//		glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
//		int dCnt, EulerDirLight* dLight,
//		int sCnt, EulerSpotLight* sLight,
//		int pCnt, EulerPointLight* pLight,
//		Shader shaderUni) {
//		glStencilMask(0x00);
//		cube->setShader(shaderUni);
//		cube->setTransform(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(5.0f, 0.5f, 5.0f), glm::vec3(0.0f));
//		cube->setMaterial(dCnt, dLight, sCnt, sLight, pCnt, pLight);
//		cube->Render(model, view, projection, viewPos);
//	}
//}