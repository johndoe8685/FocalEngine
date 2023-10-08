#include "window.h"
#include "inputManager.h"
#include "shaderManager.h"
#include "assetManager.h"
#include "mesh.h"
#include "texture.h"
#include "model.h"
#include "scene.h"
#include "game/gui.h"

/* Singletons */
Window* Window::s_instance = nullptr;
InputManager* InputManager::s_instance = nullptr;
ShaderManager* ShaderManager::s_instance = nullptr;
AssetManager* AssetManager::s_instance = nullptr;

int main()
{
	/* Initialization of Engine Here */
	if (!glfwInit()) return -1;
	Window::createInstance("mainWindow", 800, 600, false);
	InputManager::createInstance();
	ShaderManager::createInstance();
	AssetManager::createInstance();

	/* Engine Related Code Here */
	Window* mainWindow = Window::getInstance();
	ShaderManager* shaderManager = ShaderManager::getInstance();
	AssetManager* assetManager = AssetManager::getInstance();

	shaderManager->addShader("MainShader", "/res/shader/basic.frag", "/res/shader/basic.vert");
	Shader* shaderTest = shaderManager->getShader("MainShader");

	/* Game Related Code Here */
	GUI gui("Default");

	assetManager->addModel("testModel", "/res/model/dragon.obj");
	Model* testModel = assetManager->getModel("testModel");
	
	Scene testScene("Test");
	testScene.addModel("testModel", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//Animation variables
	float x = 0;
	float speed = 0.005f;
	float distance = 4.0f;
	bool isRight = true;

	/* Render Loop */
	while (mainWindow->renderLoop())
	{
		testScene.renderScene();

		//Move model between 4.0f and -4.0f
		if (x > distance)
		{
			isRight = false;
		}
		else if (x < -distance)
		{
			isRight = true;
		}

		if (isRight)
		{
			x += speed;
		}
		else
		{
			x -= speed;
		}

		testScene.setModel("testModel", glm::vec3(0.0f, 0.0f, x), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	}
	glfwTerminate();
	return 0;
}