#pragma once
//#include"../../Math/EulerMath.h"
//#include <vector>
//#include<iostream>
//#include "GLShader.h"
//#include "GLMesh.h"
//#include"GLTexture.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include"../../Resource/SourceManager.h"
//#include"GLMaterial.h"
//#include"../GLObjects/GLLight.h"
//#include"../OpenGL/GLTransform.h"
//#include"../../Game/Context/EulerContext.h"
//namespace EulerEngine {
//	class Model {
//	private:
//		EulerTransform transform;
//		std::vector<Mesh> meshes;
//		std::vector<Material> materials;
//		Shader shader;
//		std::string directory;
//		std::string name;
//	public:
//		Model() {}
//		Model(std::string const &path, std::string name) {
//			this->name = name;
//			loadModel(path);
//		}
//		void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos,
//			EulerDirLight* dLight,EulerPointLight* pLight,EulerSpotLight* sLight) {
//			shader.use();
//			shader.setMat4("projection", projection);
//			shader.setMat4("view", view);
//			model = glm::translate(model, transform.position);
//			model = glm::scale(model, transform.scale);
//			model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
//			model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
//			model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
//			shader.setMat4("model", model);
//			shader.setMat3("normalMatrix", glm::transpose(glm::inverse(model)));
//			shader.setVec3("viewPos", viewPos);
//			for (unsigned int i = 0; i < meshes.size(); i++) {
//				meshes[i].Draw(shader);
//			}
//		}
//		void setTransform(glm::vec3 pos, glm::vec3 scl, glm::vec3 rot) {
//			transform.update(pos, scl, rot);
//		}
//		void setShader(Shader shader) {
//			this->shader = shader;
//		}
//		void setMaterial(
//			int dCnt, EulerDirLight* dLight,
//			int sCnt, EulerSpotLight* sLight,
//			int pCnt, EulerPointLight* pLight) {
//			shader.use();
//			for (unsigned int i = 0; i < meshes.size(); i++) {
//				materials[i].Draw(shader, dCnt, dLight, pCnt, pLight, sCnt, sLight);
//			}
//		}
//	private:
//		void loadModel(std::string const &path) {
//			Assimp::Importer importer;
//			const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//			if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
//				std::cout << "assimp出错了" << importer.GetErrorString() << std::endl;
//				return;
//			}
//			directory = path.substr(0, path.find_last_of('/'));
//			this->processNode(scene->mRootNode, scene);
//			std::cout <<"骨骼数量: " <<meshes.size() << " 材质数量:" << materials.size() << std::endl;
//		}
//		void processNode(aiNode *node, const aiScene *scene) {
//			// 处理节点网络；
//			for (unsigned int i = 0; i < node->mNumMeshes; i++) {
//				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//				std::cout<<"骨骼名称: "<<mesh->mName.C_Str()<< std::endl;
//				meshes.push_back(this->processMesh(mesh, scene));
//				materials.push_back(this->processTexture(mesh, scene));
//			}
//			// 相同方式处理子节点；
//			for (unsigned int i = 0; i < node->mNumChildren; i++) {
//				processNode(node->mChildren[i], scene);
//			}
//		}
//		Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
//			std::vector<Vertex> vertices;
//			std::vector<unsigned int> indices;
//			//顶点相关；
//			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//				Vertex vertex;
//				// 位置相关数组；
//				glm::vec3 vectorP;
//				vectorP.x = mesh->mVertices[i].x;
//				vectorP.y = mesh->mVertices[i].y;
//				vectorP.z = mesh->mVertices[i].z;
//				vertex.Position = vectorP;
//				// 法线相关数组；
//				glm::vec3 vectorN;
//				vectorN.x = mesh->mNormals[i].x;
//				vectorN.y = mesh->mNormals[i].y;
//				vectorN.z = mesh->mNormals[i].z;
//				vertex.Normal = vectorN;
//				// 纹理坐标相关(支持最多8个纹理坐标，只关心第1个)；
//				if (mesh->mTextureCoords[0]) {
//					glm::vec2 vecT;
//					vecT.x = mesh->mTextureCoords[0][i].x;
//					vecT.y = mesh->mTextureCoords[0][i].y;
//					vertex.TexCoords = vecT;
//				}
//				else {
//					vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//				}
//				vertices.push_back(vertex);
//			}
//			//索引相关；
//			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
//				// 面：图元，包含多个索引
//				aiFace face = mesh->mFaces[i];
//				for (unsigned int j = 0; j < face.mNumIndices; j++) {
//					indices.push_back(face.mIndices[j]);
//				}
//			}
//			Mesh eulerMesh;
//			eulerMesh.setupVertex(vertices,indices);
//			return eulerMesh;
//		}
//		Material processTexture(aiMesh *mesh, const aiScene *scene) {
//			Material material;
//			//材质相关；
//			if (mesh->mMaterialIndex >= 0) {
//				aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
//				std::vector<Texture2D> diffuseMaps =
//					this->loadMaterialTextures(mat, aiTextureType_DIFFUSE);
//				for(Texture2D texture : diffuseMaps) {
//					material.addTexture(texture,DIFFUSE);
//					std::cout << "diffuse" << std::endl;
//				}
//				std::vector<Texture2D> specularMaps =
//					this->loadMaterialTextures(mat, aiTextureType_SPECULAR);
//				for (Texture2D texture : specularMaps) {
//					material.addTexture(texture, SPECULAR);
//					std::cout << "specular" << std::endl;
//				}
//			}
//			return material;
//		}
//		std::vector<Texture2D> loadMaterialTextures(aiMaterial *mat, aiTextureType type) {
//			std::vector<Texture2D> textures;
//			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
//				aiString str;
//				mat->GetTexture(type, i, &str);
//				std::string sourceName = this->name + "_texture_" + str.C_Str();
//				if (g_global_context.m_source_mgr->hasTexture(sourceName)) {
//					Texture2D oldTexture = g_global_context.m_source_mgr->getTexture(sourceName);
//					textures.push_back(oldTexture);
//				}
//				else {
//					std::string filename = directory + '/' + str.C_Str();
//					Texture2D newTexture = g_global_context.m_source_mgr->loadTexture(filename.c_str(),sourceName);
//					textures.push_back(newTexture);
//				}
//			}
//			return textures;
//		}
//	};
//}