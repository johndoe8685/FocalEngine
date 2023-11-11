#pragma once
#include <vendor/NixTools/system.h>
#include <vendor/glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include "camera.h"
#include "skybox.h"

class Shader;

class Scene : public NixTools::System
{
	struct ModelData
	{
		std::string componentName;
		std::string modelName;
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::mat4 transformation;
	};
private:
	std::vector<ModelData> m_models;
	std::unordered_map<std::string, size_t> m_modelIndexMap;
	Camera m_mainCamera;
	Skybox* m_skybox;
public:
	Scene(std::string componentName);

	void addModel(std::string componentName, std::string modelName);
	void addModel(std::string componentName, std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	void addSkybox(std::string filename);

	void setModel(std::string componentName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void setModelPosition(std::string componentName, glm::vec3 position);
	void setModelRotation(std::string componentName, glm::vec3 rotation);
	void setModelScale(std::string componentName, glm::vec3 scale);

	//TODO: Add incremental changes for model transformations

	void renderScene();
private:
	glm::mat4 setModelTransformation(ModelData previousData);
	void setMVP(glm::mat4 transformation, Shader* shader);
};