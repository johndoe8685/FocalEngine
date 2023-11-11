#include "window.h"
#include "inputManager.h"
#include "shaderManager.h"
#include "assetManager.h"
#include "mesh.h"
#include "texture.h"
#include "model.h"
#include "scene.h"
#include "camera.h"
#include "game/gui.h"

/* Singletons */
Window* Window::s_instance = nullptr;
InputManager* InputManager::s_instance = nullptr;
ShaderManager* ShaderManager::s_instance = nullptr;
AssetManager* AssetManager::s_instance = nullptr;

double G_DELTATIME = 0.0;

int main()
{
	/* Initialization of Engine Here */
	if (!glfwInit()) return -1;
	Window::createInstance("mainWindow", 800, 600, false);
	InputManager::createInstance();
	ShaderManager::createInstance(Window::getInstance());
	AssetManager::createInstance();

	/* Engine Related Code Here */
	Window* mainWindow = Window::getInstance();
	ShaderManager* shaderManager = ShaderManager::getInstance();
	AssetManager* assetManager = AssetManager::getInstance();

	shaderManager->addShader("MainShader", "/res/shader/basic.frag", "/res/shader/basic.vert");
	assetManager->addModel("errorModel", "/res/model/error.obj");

	/* Game Related Code Here */
	GUI gui("Default");

	assetManager->addModel("DragonModel", "/res/model/dragon.obj");
	assetManager->addModel("FloorModel", "/res/model/floor.obj");

	Scene testScene("Test");
	testScene.addSkybox("Blue");

	testScene.addModel("Dragon", "DragonModel", glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	testScene.addModel("Floor", "FloorModel", glm::vec3(0.0f, -1.0f, -2.5f), glm::vec3(0.0f), glm::vec3(1.0f));

	//Variables
	float curAngle = 0.0f;
	float speed = 0.0f;
	constexpr float toRadians = 3.14159265358979323846f / 180.f;

	/* Render Loop */
	while (mainWindow->renderLoop(&G_DELTATIME))
	{
		shaderManager->update(&G_DELTATIME);
		testScene.renderScene();

		//Rotate the dragon
		speed = 80.0f * toRadians * shaderManager->getDeltatime();
		curAngle += speed;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		testScene.setModelRotation("DragonModel", glm::vec3(0.0f, curAngle, 0.0f));
	}
	glfwTerminate();
	return 0;
}