#include "assetManager.h"

AssetManager::AssetManager()
	:System("Default", "AssetManager")
{
}

void AssetManager::createInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new AssetManager();
	}
	else
	{
		s_instance->debugger.giveMessage(NixTools::Error, "AssetManager was already created!!");
	}
}

AssetManager* AssetManager::getInstance()
{
	if (s_instance != nullptr)
	{
		return s_instance;
	}
	else
	{
		NixTools::Debugger tmp("AssetManager");
		tmp.giveMessage(NixTools::Error, "AssetManager isnt created! Create AssetManager first.");
	}
}

template<typename T>
T* AssetManager::find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<T>> map)
{
	return map[componentName].get();
}

void AssetManager::addModel(std::string componentName, std::string path)
{
	std::shared_ptr<Model> model = std::make_shared<Model>(componentName, path);
	m_modelMap[componentName] = model;
}

Model* AssetManager::getModel(std::string componentName)
{
	return find(componentName, m_modelMap);
}
