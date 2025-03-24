#include "engine.h"
#include "game/gui.h"
#include "scene.h"

GameEngine::GameEngine()
	:System("Default", "GameEngine")
{
	/* Initialization of Engine Here */
	Window::createInstance("mainWindow", 1280, 720, false);
	InputManager::createInstance();
	ShaderManager::createInstance(Window::getInstance());
	AssetManager::createInstance();
	CoreGUI::createInstance(Window::getInstance(), "Engine");

	window = Window::getInstance();
	inputManager = InputManager::getInstance();
	shaderManager = ShaderManager::getInstance();
	assetManager = AssetManager::getInstance();
	engineGUI = CoreGUI::getInstance();

	/* Initialize NixEngine's default assets */
	defaultAssetsInit();
}

void GameEngine::defaultAssetsInit()
{
	/* Default Shaders */
	shaderManager->addShader("MainShader", "/res/shader/basic.frag", "/res/shader/basic.vert");

	/* Default Models */
	assetManager->addModel("errorModel", "/res/model/error.obj");
}

void GameEngine::run()
{

	/* Game Related Code Here */
	GUI gui("Default");

	assetManager->addModel("DragonModel", "/res/model/dragon.obj");
	assetManager->addModel("FloorModel", "/res/model/floor.obj");
	//assetManager->addModel("sponza_v2", "/res/model/sponza_v2.gltf");

	Scene testScene("Test");
	testScene.addSkybox("Blue");
	//testScene.addSkybox("Black");

	//Lets create a test Shader with moving checkerboard pattern
	shaderManager->addShader("checkerShader", "/res/shader/test.frag", "/res/shader/test.vert");
	shaderManager->addShader("TestFramerateShader", "/res/shader/testFramerate.frag", "/res/shader/TestFramerate.vert");
	Shader* testShader = shaderManager->getShader("checkerShader");
	Shader* frameRateShader = shaderManager->getShader("TestFramerateShader"); 

	testScene.addModel("Dragon", "DragonModel", glm::vec3(0.0f, 0.0f, -2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f), nullptr);
	testScene.addModel("Floor", "FloorModel", glm::vec3(0.0f, -1.0f, -2.5f), glm::vec3(0.0f), glm::vec3(1.0f), nullptr);
	testScene.addModel("ErrorTest", "errorModel", glm::vec3(0.0f, 2.0f, -2.5f), glm::vec3(0.0f), glm::vec3(1.0f), testShader);

	testScene.addAmbientLight("Skylight", glm::vec3(1.0f), glm::vec3(0.0f), 0.5f);
	testScene.addDirectionalLight("Sunlight", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(2.0f, -1.0f, 2.0f), 0.8f);
	testScene.addPointLight("TestPoint", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 3.0f, -2.5f), 1.0f);

	testScene.useLight("Sunlight");
	testScene.useLight("Skylight");
	//testScene.useLight("TestPoint");

	//Variables
	float curAngle = 0.0f;
	float speed = 0.0f;
	constexpr float toRadians = 3.14159265358979323846f / 180.f;

	Shader* shader = shaderManager->getShader("MainShader");

	unsigned int statUpdate = 0;
	float wanted_fps = 0.33;
	bool shouldRender = true;
	float renderStatUpdate = 0;

	/* Start ApplicationLoop */
	while (window->renderLoop(&engineData.deltaTime, &engineData.elapsedTime))
	{
		shaderManager->update(&engineData.deltaTime);

		testShader->SetUniform1f("elapsedTime", engineData.elapsedTime);
		//frameRateShader->SetUniform1f("elapsedTime", engineData.elapsedTime);
		//frameRateShader->SetUniform1f("wanted_fps", wanted_fps);


		//FrameRate Test
		if (engineData.elapsedTime - renderStatUpdate > wanted_fps)
		{
			frameRateShader->SetUniform1f("shouldRenderTest", 1.0f);
			debugger.giveMessage(NixTools::Info, "Works?");
			renderStatUpdate = engineData.elapsedTime;
		}
		else
		{
			frameRateShader->SetUniform1f("shouldRenderTest", 0.0f);
		}

		//Rotate the dragon
		speed = 80.0f * toRadians * shaderManager->getDeltatime();
		curAngle += speed;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}


		if (engineData.elapsedTime - statUpdate > 1)
		{
			debugger.giveMessage(NixTools::Info, "Time:", (float)(1 / engineData.deltaTime));
			statUpdate = engineData.elapsedTime;
		}

		/*
		//hook dragon into camera
		glm::vec3 cameraPosition = testScene.getCameraPosition();
		cameraPosition.z = cameraPosition.z - 3.0f;
		testScene.setModelPosition("DragonModel", cameraPosition);
		*/

		testScene.setModelRotation("DragonModel", glm::vec3(0.0f, curAngle, 0.0f));

		//Render
		testScene.renderScene();


		/* Start New Frame and make the backend ready */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		engineGUI->run();


		ImGui::Begin("Framerate test");
		ImGui::SliderFloat("Wanted Framerate", &wanted_fps, 0.001, 0.5);
		ImGui::End();

		/* Render all GUI */
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
