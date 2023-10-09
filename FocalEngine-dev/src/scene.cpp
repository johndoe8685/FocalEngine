#include "scene.h"
#include <vendor/glm/gtc/matrix_transform.hpp>
#include "shaderManager.h"
#include "assetManager.h"

Scene::Scene(std::string componentName)
	:System(componentName, "Scene")
{
}

void Scene::addModel(std::string modelName)
{
	ModelData data;
	data.modelName = modelName;
	m_models.emplace_back(data);
	m_modelIndexMap[modelName] = m_models.size() - 1;
}

void Scene::addModel(std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	ModelData data;
	data.modelName = modelName;
	data.position = position;
	data.rotation = rotation;
	data.scale = scale;
	m_models.emplace_back(data);
	m_modelIndexMap[modelName] = m_models.size() - 1;
}

void Scene::setModel(std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	m_models[m_modelIndexMap[modelName]].position = position;
	m_models[m_modelIndexMap[modelName]].rotation = rotation;
	m_models[m_modelIndexMap[modelName]].scale = scale;
}

void Scene::setModelPosition(std::string modelName, glm::vec3 position)
{
	m_models[m_modelIndexMap[modelName]].position = position;
}

void Scene::setModelRotation(std::string modelName, glm::vec3 rotation)
{
	m_models[m_modelIndexMap[modelName]].rotation = rotation;
}

void Scene::setModelScale(std::string modelName, glm::vec3 scale)
{
	m_models[m_modelIndexMap[modelName]].scale = scale;
}

void Scene::setMVP(size_t index, Shader* shader)
{
	glm::mat4 mvp(1.0f);
	ModelData data = m_models[index];
	mvp = glm::translate(mvp, data.position);
	mvp = glm::scale(mvp, data.scale);
	mvp = glm::rotate(mvp, data.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	mvp = glm::rotate(mvp, data.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	mvp = glm::rotate(mvp, data.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	shader->SetUniformMatrix4fv("model", mvp);

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(90.0f), (800.0f / 600.0f), 0.1f, 1000.0f);
	shader->SetUniformMatrix4fv("projection", projection);


	//TODO: Store model transformations that is not changing into an array
	//TODO: Move Setting Uniform into renderScene() function;
	
}

void Scene::renderScene()
{
	AssetManager* assetManager = AssetManager::getInstance();
	ShaderManager* shaderManager = ShaderManager::getInstance();
	Shader* mainShader = shaderManager->getShader("MainShader");
	for (size_t i = 0; i < m_models.size(); i++)
	{
		setMVP(i, mainShader);
		mainShader->Bind();
		Model* modelData = assetManager->getModel(m_models[i].modelName);
		modelData->RenderModel();
		mainShader->Unbind();
	}	
}
