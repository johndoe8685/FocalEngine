#include "scene.h"

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

void Scene::addModel(std::string componentName, std::string modelName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Shader* modelShader)
{
	//TODO Check if model does exist in assetManager
	ModelData data;
	data.componentName = componentName;
	data.modelName = modelName;
	data.position = position;
	data.rotation = rotation;
	data.scale = scale;
	data.transformation = setModelTransformation(data);
	data.modelShader = modelShader;
	m_models.emplace_back(data);
	m_modelIndexMap[componentName] = m_models.size() - 1;
}

void Scene::addAmbientLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity)
{
	CoreLight* light = new AmbientLight(lightName, color, position, intensity)	;
	m_lights.emplace_back(light);
	m_lightIndexMap[lightName] = m_lights.size() - 1;
}

void Scene::addDirectionalLight(std::string lightName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float intensity)
{
	CoreLight* light = new DirectionalLight(lightName, color, position, direction, intensity);
	m_lights.emplace_back(light);
	m_lightIndexMap[lightName] = m_lights.size() - 1;
}

void Scene::addPointLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity)
{
	CoreLight* light = new PointLight(lightName, color, position, intensity);
	m_lights.emplace_back(light);
	m_lightIndexMap[lightName] = m_lights.size() - 1;
}

void Scene::useLight(std::string lightName)
{
	if (m_lightIndexMap.count(lightName) == 1)
	{
		m_lights[m_lightIndexMap[lightName]]->useLight();
	}
	else
	{
		debugger.giveMessage(NixTools::Error, "Light does not exist", lightName);
	}
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

glm::vec3 Scene::getCameraPosition()
{
	return m_mainCamera.getPosition();
}

void Scene::setMVP(glm::mat4 transformation, Shader* shader)
{
	ShaderManager* shaderManager = ShaderManager::getInstance();
	int width, height;
	shaderManager->getWindowSize(&width, &height);

	//TODO put this projection algorithm into Camera class
	if(width != 0 && height != 0) shaderManager->projection = glm::perspective(glm::radians(90.0f), ((float)width / (float)height), 0.1f, 1000.0f);

	shaderManager->mvp = shaderManager->projection * shaderManager->view * transformation;

	shader->SetUniformMatrix4fv("mvp", shaderManager->mvp);
	shader->SetUniformMatrix4fv("model", transformation);
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


	shaderManager->view = m_mainCamera.calculateViewMatrix();
	glm::vec3 cameraPosition = m_mainCamera.getPosition();
	if (m_skybox != nullptr) m_skybox->DrawSkybox(shaderManager->view, shaderManager->projection);

	m_mainCamera.update();

	for (size_t i = 0; i < m_models.size(); i++)
	{
		Shader* modelShader = nullptr;
		Model* modelData = assetManager->getModel(m_models[i].modelName);

		if (m_models[i].modelShader == nullptr)
		{
			modelShader = shaderManager->getShader("MainShader");
			modelShader->SetUniform3f("cameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);
		}
		else
		{
			modelShader = m_models[i].modelShader;
		}

		setMVP(m_models[i].transformation, modelShader);

		modelShader->Bind();
		modelData->RenderModel();
		modelShader->Unbind();
	}
}
