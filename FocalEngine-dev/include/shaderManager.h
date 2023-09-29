#pragma once
#include <unordered_map>
#include <memory>
#include <vendor/NixTools/system.h>
#include "shader.h"

class ShaderManager : public NixTools::System
{
private:
	static ShaderManager* s_instance;
	ShaderManager();

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	Shader* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map);
public:
	static void createInstance();
	static ShaderManager* getInstance();

	void addShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader);
	Shader* getShader(std::string componentName);
};