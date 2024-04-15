#pragma once
#include <vendor/NixTools/system.h>
#include <vendor/glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <vendor/glm/gtc/matrix_transform.hpp>
#include "shaderManager.h"
#include "assetManager.h"
#include "camera.h"
#include "skybox.h"
#include "lights/corelight.h"
#include "lights/ambientLight.h"
#include "lights/directionalLight.h"
#include "lights/pointLight.h"

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

	std::vector<CoreLight*> m_lights;
	std::unordered_map<std::string, size_t> m_lightIndexMap;

	Camera m_mainCamera;
	Skybox* m_skybox;
public:
	Scene(std::string componentName);

	void addModel(std::string componentName, std::string modelName);
	void addModel(std::string componentName, std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	
	void setModel(std::string componentName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void setModelPosition(std::string componentName, glm::vec3 position);
	void setModelRotation(std::string componentName, glm::vec3 rotation);
	void setModelScale(std::string componentName, glm::vec3 scale);
	
	void addAmbientLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity);
	void addDirectionalLight(std::string lightName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float intensity);
	void addPointLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity);

	void useLight(std::string lightName);

	void addSkybox(std::string filename);

	//TODO: Add incremental changes for model transformations

	void renderScene();
private:
	glm::mat4 setModelTransformation(ModelData previousData);
	void setMVP(glm::mat4 transformation, Shader* shader);
};