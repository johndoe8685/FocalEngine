#include "window.h"
#include "inputManager.h"
#include "shaderManager.h"
#include "assetManager.h"
#include "mesh.h"
#include "texture.h"
#include "model.h"
#include "scene.h"
#include "camera.h"
#include "core/coreGUI.h"
#include "core/console.h"
#include "game/gui.h" 

/* Singletons */
Window* Window::s_instance = nullptr;
InputManager* InputManager::s_instance = nullptr;
ShaderManager* ShaderManager::s_instance = nullptr;
AssetManager* AssetManager::s_instance = nullptr;
CoreGUI* CoreGUI::s_instance = nullptr;

double G_DELTATIME = 0.0;
double G_ELAPSEDTIME = 0.0;

int testJolt();

int main()
{
	/* Init glfw before Engine init */
	if (!glfwInit()) return -1;

	NixTools::Debugger dbg("Default", "GameEngine");

	/* Engine Related Code Here */
	Window* mainWindow = Window::getInstance();
	ShaderManager* shaderManager = ShaderManager::getInstance();
	AssetManager* assetManager = AssetManager::getInstance();

	shaderManager->addShader("MainShader", "/res/shader/basic.frag", "/res/shader/basic.vert");
	shaderManager->addShader("GridShader", "/res/shader/grid.frag", "/res/shader/grid.vert");
	shaderManager->addShader("TestShader", "/res/shader/test.frag", "/res/shader/test.vert");
	shaderManager->addShader("TestFramerateShader", "/res/shader/testFramerate.frag", "/res/shader/TestFramerate.vert");
	assetManager->addModel("errorModel", "/res/model/error.obj");

	Shader* gridShader = shaderManager->getShader("GridShader");
	Shader* testShader = shaderManager->getShader("TestShader");
	Shader* frameRateShader = shaderManager->getShader("TestFramerateShader"); 

	CoreGUI::createInstance(mainWindow, "Default");
	CoreGUI* coreGUI = CoreGUI::getInstance();

	/* Game Related Code Here */
	GUI gui("Default");

	assetManager->addModel("DragonModel", "/res/model/dragon.obj");
	assetManager->addModel("FloorModel", "/res/model/floor.obj");
	//assetManager->addModel("sponza_v2", "/res/model/sponza_v2.gltf");

	Scene testScene("Test");
	testScene.addSkybox("Blue");
	//testScene.addSkybox("Black");

	testScene.addModel("Dragon", "DragonModel", glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f), frameRateShader);
	testScene.addModel("Floor", "FloorModel", glm::vec3(0.0f, -1.0f, -2.5f), glm::vec3(0.0f), glm::vec3(1.0f), nullptr);
	//testScene.addModel("Sponza", "sponza", glm::vec3(0.0f, -1.0f, -2.5f), glm::vec3(0.0f), glm::vec3(0.01f));
	//testScene.addModel("Sponza_v2", "sponza_v2", glm::vec3(0.0f, -1.0f, -2.5f), glm::vec3(0.0f), glm::vec3(0.01f), nullptr);


	//testScene.addAmbientLight("Skylight", glm::vec3(0.529f, 0.808f, 0.922f), glm::vec3(0.0f, 0.0f, 0.0f), 0.2f);
	testScene.addAmbientLight("Skylight", glm::vec3(1.0f), glm::vec3(0.0f), 0.5f);
	testScene.addDirectionalLight("Sunlight", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(2.0f, -1.0f, 2.0f), 0.8f);
	testScene.addPointLight("TestPoint", glm::vec3(1.0f), glm::vec3(0.0f, 3.0f,	 -2.5f), 1.0f);

	testScene.useLight("Sunlight");
	testScene.useLight("Skylight");
	//testScene.useLight("TestPoint");

	//Variables
	float curAngle = 0.0f;
	float speed = 0.0f;
	constexpr float toRadians = 3.14159265358979323846f / 180.f;

	Shader* shader = shaderManager->getShader("MainShader");

	unsigned int statUpdate = 0;

	/* Render Loop */
	while (mainWindow->renderLoop(&G_DELTATIME, &G_ELAPSEDTIME))
	{
		shaderManager->update(&G_DELTATIME);

		frameRateShader->SetUniform1f("elapsedTime", G_ELAPSEDTIME);

		//Rotate the dragon
		speed = 80.0f * toRadians * shaderManager->getDeltatime();
		curAngle += speed;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}
	
		/*
		if (G_ELAPSEDTIME - statUpdate > 1)
		{
			dbg.giveMessage(NixTools::Info, "FPS", (float)(1 / G_DELTATIME));
			statUpdate = G_ELAPSEDTIME;
		}
		*/

		/*
		//hook dragon into camera
		glm::vec3 cameraPosition = testScene.getCameraPosition();
		cameraPosition.z = cameraPosition.z - 3.0f;
		testScene.setModelPosition("DragonModel", cameraPosition);
		*/

		testScene.setModelRotation("DragonModel", glm::vec3(0.0f, curAngle, 0.0f));

		//Render
		testScene.renderScene();

		coreGUI->run();
	}

	testJolt();

	glfwTerminate();
	return 0;
}