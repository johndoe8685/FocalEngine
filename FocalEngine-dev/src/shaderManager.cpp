#include <shaderManager.h>

ShaderManager::ShaderManager()
	:System("Default", "ShaderManager")
{
}

void ShaderManager::createInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ShaderManager();
	}
	else
	{
		s_instance->debugger.giveMessage(NixTools::Debugger::Error, "ShaderManager was already created!!");
	}
}

ShaderManager* ShaderManager::getInstance()
{
	if (s_instance != nullptr)
	{
		return s_instance;
	}
	else
	{
		NixTools::Debugger tmp("ShaderManager");
		tmp.giveMessage(NixTools::Debugger::Error, "ShaderManager isnt created! Create InputManager first.");
	}
}

Shader* ShaderManager::find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map)
{
	return map[componentName].get();
}

void ShaderManager::addShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(componentName, fragmentShader, vertexShader);
	m_shaderMap[componentName] = shader;
}

Shader* ShaderManager::getShader(std::string componentName)
{
	Shader* shader = find(componentName, m_shaderMap);
	return shader;
}