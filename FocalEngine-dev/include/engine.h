#pragma once
#include "window.h"
#include "assetManager.h"
#include "shaderManager.h"
#include "inputManager.h"
#include "core/coreGUI.h"


struct EngineData
{
	float deltaTime;
	int windowWidth;
	int windowHeight;
	float framerate;
	double elapsedTime;
	unsigned int elapsedSeconds;
};

struct GameData
{
	glm::vec3 playerPosition;
};

struct CameraData
{
	glm::vec3 cameraPosition;
};

class GameEngine : public NixTools::System
{
private:
	/* Engine Systems */
	Window* window;
	AssetManager* assetManager;
	ShaderManager* shaderManager;
	InputManager* inputManager;
	CoreGUI* engineGUI;

	/* Data structures */
	EngineData engineData;
	GameData gameData;
	CameraData cameraData;
public:
	GameEngine();

	void defaultAssetsInit();
	void run();
};