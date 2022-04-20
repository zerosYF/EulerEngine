#pragma once
#include"../../Math/EulerMath.h"
#include <vector>
#include "GLShader.h"
#include "GLMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include"../../triangle.h"

using namespace std;
class Model {
public:
	Model() {}
	Model(string const &path) {
		loadModel(path);
	}
	void Draw(Shader shader) {
		for (int i = 0; i < meshes.size(); i++) {
			meshes[i].Draw(shader);
		}
	}
	vector<Mesh> getMeshes() {
		return this->meshes;
	}
	vector<Texture> getTextures() {
		return this->textures_loaded;
	}
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	void loadModel(string const &path) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path,aiProcess_Triangulate|aiProcess_FlipUVs);
		if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
			cout << "assimp������" << importer.GetErrorString() << endl;
			return;
		}
		directory = path.substr(0,path.find_last_of('/'));
		this->processNode(scene->mRootNode,scene);
	}
	void processNode(aiNode *node, const aiScene *scene) {
		// ����ڵ����磻
		for (int i = 0; i < node -> mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(this->processMesh(mesh,scene));
		}
		// ��ͬ��ʽ�����ӽڵ㣻
		for (int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i],scene);
		}
	}
	Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		//������أ�
		for (int i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;
			// λ��������飻
			glm::vec3 vectorP;
			vectorP.x = mesh->mVertices[i].x;
			vectorP.y = mesh->mVertices[i].y;
			vectorP.z = mesh->mVertices[i].z;
			vertex.Postion = vectorP;
			// ����������飻
			glm::vec3 vectorN;
			vectorN.x = mesh->mNormals[i].x;
			vectorN.y = mesh->mNormals[i].y;
			vectorN.z = mesh->mNormals[i].z;
			vertex.Normal = vectorN;
			// �����������(֧�����8���������ֻ꣬���ĵ�1��)��
			if (mesh->mTextureCoords[0]) {
				glm::vec2 vecT;
				vecT.x = mesh->mTextureCoords[0][i].x;
				vecT.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vecT;
			}
			else {
				vertex.TexCoords = glm::vec2(0.0f,0.0f);
			}
			vertices.push_back(vertex);
		}
		//������أ�
		for (int i = 0; i < mesh->mNumFaces; i++) {
			// �棺ͼԪ�������������
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
		//������أ�
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = 
				this->loadMaterialTextures(material,aiTextureType_DIFFUSE,"texture_diffuse");
			textures.insert(textures.end(),diffuseMaps.begin(),diffuseMaps.end());
			vector<Texture> specularMaps =
				this->loadMaterialTextures(material,aiTextureType_SPECULAR,"texture_specular");
			textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
		}
		return Mesh(vertices,indices,textures);
	}
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) {
		vector<Texture> textures;
		for (int i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type,i,&str);
			bool skip = false;
			for (int j = 0; j < textures_loaded.size(); j++) {
				if (strcmp(textures_loaded[j].path.C_Str(),str.C_Str())==0) {
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {
				Texture texture;
				string filename = directory + '/' + str.C_Str();
				texture.id = addTexture(filename.c_str());
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);
			}
		}
		return textures;
	}
};