#include "scene.h"
#include <vendor/glm/gtc/matrix_transform.hpp>
#include "shaderManager.h"
#include "assetManager.h"

Scene::Scene(std::string componentName)
	:System(componentName, "Scene"), m_mainCamera("MainCamera", glm::vec3(0.0f), glm::vec2(-90.0f, 0.0f))
{
}

void Scene::addModel(std::string componentName,  std::string modelName)
{
	ModelData data;
	data.modelName = modelName;
	m_models.emplace_back(data);
	m_modelIndexMap[modelName] = m_models.size() - 1;
}

void Scene::addModel(std::string componentName, std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	ModelData data;
	data.componentName = componentName;
	data.modelName = modelName;
	data.position = position;
	data.rotation = rotation;
	data.scale = scale;
	data.transformation = setModelTransformation(data);
	m_models.emplace_back(data);
	m_modelIndexMap[componentName] = m_models.size() - 1;
}

void Scene::addSkybox(std::string filename)
{
	m_skybox = new Skybox(m_componentName, filename);
}

void Scene::setModel(std::string componentName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	m_models[m_modelIndexMap[componentName]].position = position;
	m_models[m_modelIndexMap[componentName]].rotation = rotation;
	m_models[m_modelIndexMap[componentName]].scale = scale;
	m_models[m_modelIndexMap[componentName]].transformation = setModelTransformation(m_models[m_modelIndexMap[componentName]]);
}

void Scene::setModelPosition(std::string componentName, glm::vec3 position)
{
	m_models[m_modelIndexMap[componentName]].position = position;
	m_models[m_modelIndexMap[componentName]].transformation = setModelTransformation(m_models[m_modelIndexMap[componentName]]);
}

void Scene::setModelRotation(std::string componentName, glm::vec3 rotation)
{
	m_models[m_modelIndexMap[componentName]].rotation = rotation;
	m_models[m_modelIndexMap[componentName]].transformation = setModelTransformation(m_models[m_modelIndexMap[componentName]]);
}

void Scene::setModelScale(std::string componentName, glm::vec3 scale)
{
	m_models[m_modelIndexMap[componentName]].scale = scale;
	m_models[m_modelIndexMap[componentName]].transformation = setModelTransformation(m_models[m_modelIndexMap[componentName]]);
}

void Scene::setMVP(glm::mat4 transformation, Shader* shader)
{
	ShaderManager* shaderManager = ShaderManager::getInstance();
	int width, height;
	shaderManager->getWindowSize(&width, &height);

	if(width != 0 && height != 0) shaderManager->projection = glm::perspective(glm::radians(90.0f), ((float)width / (float)height), 0.1f, 1000.0f);

	shaderManager->mvp = shaderManager->projection * shaderManager->view * transformation;

	shader->SetUniformMatrix4fv("mvp", shaderManager->mvp);
}

glm::mat4 Scene::setModelTransformation(ModelData data)
{
	glm::mat4 transformation(1.0f);
	transformation = glm::translate(transformation, data.position);
	transformation = glm::scale(transformation, data.scale);
	transformation = glm::rotate(transformation, data.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	transformation = glm::rotate(transformation, data.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transformation = glm::rotate(transformation, data.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	return transformation;
}

void Scene::renderScene()
{
	AssetManager* assetManager = AssetManager::getInstance();
	ShaderManager* shaderManager = ShaderManager::getInstance();
	Shader* mainShader = shaderManager->getShader("MainShader");

	shaderManager->view = m_mainCamera.calculateViewMatrix();
	if (m_skybox != nullptr) m_skybox->DrawSkybox(shaderManager->view, shaderManager->projection);

	m_mainCamera.update();

	for (size_t i = 0; i < m_models.size(); i++)
	{
		Model* modelData = assetManager->getModel(m_models[i].modelName);
		setMVP(m_models[i].transformation, mainShader);

		mainShader->Bind();
		modelData->RenderModel();
		mainShader->Unbind();
	}
}
