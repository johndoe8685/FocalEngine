#pragma once
#include <vendor/NixTools/system.h>
#include <vendor/glm/glm.hpp>
#include <vector>
#include <unordered_map>

class Shader;

class Scene : public NixTools::System
{
	struct ModelData
	{
		std::string modelName;
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	};
private:
	std::vector<ModelData> m_models;
	std::unordered_map<std::string, size_t> m_modelIndexMap;
public:
	Scene(std::string componentName);

	void addModel(std::string modelName);
	void addModel(std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	void setModel(std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void setModelPosition(std::string modelName, glm::vec3 position);
	void setModelRotation(std::string modelName, glm::vec3 rotation);
	void setModelScale(std::string modelName, glm::vec3 scale);

	//TODO: Add individual model transformations
	//TODO: Add incremental changes for model transformations

	void renderScene();
private:
	void setMVP(size_t index, Shader* shader);
};