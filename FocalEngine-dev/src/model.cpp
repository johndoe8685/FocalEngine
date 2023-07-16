#include "model.h"

Model::Model(std::string componentName, std::string path)
	:System("Model", componentName)
{
	directory.changePath(path);
	Assimp::Importer importer;
	m_scene = importer.ReadFile(directory.getPath(), aiProcess_Triangulate);
}