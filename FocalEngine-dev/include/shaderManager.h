#pragma once
#include <unordered_map>
#include <memory>
#include <vendor/NixTools/system.h>
#include <vendor/glm/glm.hpp>
#include "shader.h"

class Window;

class ShaderManager : public NixTools::System
{
private:
	//Singleton Constructor and  pointer
	ShaderManager(Window* window);
	static ShaderManager* s_instance;
	Window* m_curWindow;
	float m_deltatime;

	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
	Shader* find(std::string componentName, std::unordered_map<std::string, std::shared_ptr<Shader>> map);
public:
	glm::mat4 mvp;
	glm::mat4 projection;
	glm::mat4 view;
public:
	//Singleton creation
	static void createInstance(Window* window);
	static ShaderManager* getInstance();

	void setCurrentWindow(Window* window);

	void addShader(std::string componentName, const std::string& fragmentShader, const std::string& vertexShader);
	Shader* getShader(std::string componentName);

	void update(float* deltatime);

	double getDeltatime();

	void getWindowSize(int* width, int* height);
};