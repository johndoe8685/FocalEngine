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
	data.transformation = setModelTransformation(data);
	m_models.emplace_back(data);
	m_modelIndexMap[modelName] = m_models.size() - 1;
}

void Scene::setModel(std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	m_models[m_modelIndexMap[modelName]].position = position;
	m_models[m_modelIndexMap[modelName]].rotation = rotation;
	m_models[m_modelIndexMap[modelName]].scale = scale;
	m_models[m_modelIndexMap[modelName]].transformation = setModelTransformation(m_models[m_modelIndexMap[modelName]]);
}

void Scene::setModelPosition(std::string modelName, glm::vec3 position)
{
	m_models[m_modelIndexMap[modelName]].position = position;
	m_models[m_modelIndexMap[modelName]].transformation = setModelTransformation(m_models[m_modelIndexMap[modelName]]);
}

void Scene::setModelRotation(std::string modelName, glm::vec3 rotation)
{
	m_models[m_modelIndexMap[modelName]].rotation = rotation;
	m_models[m_modelIndexMap[modelName]].transformation = setModelTransformation(m_models[m_modelIndexMap[modelName]]);
}

void Scene::setModelScale(std::string modelName, glm::vec3 scale)
{
	m_models[m_modelIndexMap[modelName]].scale = scale;
	m_models[m_modelIndexMap[modelName]].transformation = setModelTransformation(m_models[m_modelIndexMap[modelName]]);
}

void Scene::setMVP(glm::mat4 transformation, Shader* shader)
{
	glm::mat4 mvp;
	glm::mat4 projection(1.0f);

	projection = glm::perspective(glm::radians(90.0f), (800.0f / 600.0f), 0.1f, 1000.0f);
	mvp = projection * transformation;

	shader->SetUniformMatrix4fv("mvp", mvp);
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

	for (size_t i = 0; i < m_models.size(); i++)
	{
		Model* modelData = assetManager->getModel(m_models[i].modelName);
		setMVP(m_models[i].transformation, mainShader);

		mainShader->Bind();
		modelData->RenderModel();
		mainShader->Unbind();
	}
}
