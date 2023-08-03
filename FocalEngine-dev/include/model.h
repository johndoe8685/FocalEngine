#pragma once
#include <vector>
#include <vendor/NixTools/system.h>
#include <vendor/assimp/scene.h>
#include <vendor/assimp/Importer.hpp>
#include <vendor/assimp/postprocess.h>
#include "mesh.h"
#include "texture.h"


class Model : public NixTools::System
{
private:
	const Assimp::Importer m_importer;
	const aiScene* m_scene;

	std::vector<Mesh*> m_meshList;
	std::vector<Texture*> m_textureList;
	std::vector<unsigned int> m_textureID;

public:
	Model(std::string componentName, std::string path);
	void RenderModel();
private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void ProcessTexture(const aiScene* scene);
};
