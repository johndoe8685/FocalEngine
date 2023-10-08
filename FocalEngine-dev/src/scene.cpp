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
	ModelData data;
	data.modelName = modelName;
	data.position = position;
	data.rotation = rotation;
	data.scale = scale;
	m_models.emplace_back(data);
}

void Scene::setMVP(size_t index)
{
	glm::mat4 mvp(1.0f);
	ModelData data = m_models[index];
	mvp = glm::translate(mvp, data.position);
	mvp = glm::scale(mvp, data.scale);
	mvp = glm::rotate(mvp, data.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	mvp = glm::rotate(mvp, data.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	mvp = glm::rotate(mvp, data.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	//TODO: Store model transformations that is not changing into an array
	//TODO: Move Setting Uniform into renderScene() function;
	ShaderManager* shaderManager = ShaderManager::getInstance();
	Shader* mainShader = shaderManager->getShader("MainShader");
	mainShader->SetUniformMatrix4fv("mvp", mvp);
}

void Scene::renderScene()
{
	AssetManager* assetManager = AssetManager::getInstance();
	for (size_t i = 0; i < m_models.size(); i++)
	{
		setMVP(i);
		Model* modelData = assetManager->getModel(m_models[i].modelName);
		modelData->RenderModel();
	}	
}
