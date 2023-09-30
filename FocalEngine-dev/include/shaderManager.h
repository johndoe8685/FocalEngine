#pragma once
#include <unordered_map>
#include <memory>
#include <vendor/NixTools/system.h>
#include "shader.h"

class ShaderManager : public NixTools::System
{
private:
	//Singleton Constructor and  pointer
	ShaderManager();
	static ShaderManager* s_instance;

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	Shader* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map);
public:
	//Singleton creation
	static void createInstance();
	static ShaderManager* getInstance();

	void addShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader);
	Shader* getShader(std::string componentName);
};