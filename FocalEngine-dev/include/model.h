#pragma once
#include <vendor/NixTools/system.h>
#include <vendor/assimp/scene.h>
#include <vendor/assimp/Importer.hpp>
#include <vendor/assimp/postprocess.h>


class Model : public NixTools::System
{
private:
	const aiScene* m_scene;
public:
	Model(std::string componentName, std::string path);
};
