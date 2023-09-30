#pragma once
#include "vendor/NixTools/system.h"
#include <memory>
#include <unordered_map>
#include "model.h"

class AssetManager : public NixTools::System
{
private:
	//Singleton Constructor and  pointer
	AssetManager();
	static AssetManager* s_instance;

	std::unordered_map<std::string, std::shared_ptr<Model>> m_modelMap;
	template<typename T> T* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<T>> map);
public:
	//Singleton creation
	static void createInstance();
	static AssetManager* getInstance();
	
	void addModel(std::string componentName, std::string path);
	
	Model* getModel(std::string componentName);

};