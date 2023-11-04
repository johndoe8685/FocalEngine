#pragma once
#include <unordered_map>
#include <memory>
#include <vendor/NixTools/system.h>
#include "shader.h"

class Window;

class ShaderManager : public NixTools::System
{
private:
	//Singleton Constructor and  pointer
	ShaderManager(Window* window);
	static ShaderManager* s_instance;
	Window* m_curWindow;

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	Shader* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map);
public:
	//Singleton creation
	static void createInstance(Window* window);
	static ShaderManager* getInstance();

	void setCurrentWindow(Window* window);

	void addShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader);
	Shader* getShader(std::string componentName);

	void getWindowSize(int* width, int* height);
};