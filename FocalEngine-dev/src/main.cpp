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
	
	std::vector<Vertex> test_vertices;
	test_vertices.push_back( { glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) } );
	test_vertices.push_back({ glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	test_vertices.push_back({ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f) });

	std::vector<unsigned int> test_indices;
	test_indices.push_back(0);
	test_indices.push_back(1);
	test_indices.push_back(2);

	Mesh testMesh(test_vertices, test_indices);

	assetManager->addModel("testModel", "/res/model/dragon.obj");
	Model* testModel = assetManager->getModel("testModel");

	Scene testScene("Test");
	testScene.addModel("testModel", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	Texture testTexture("/res/texture/error.png");
	testTexture.LoadTexture();
	testTexture.Bind();

	float x = 0;

	/* Render Loop */
	while (mainWindow->renderLoop())
	{
		shaderTest->Bind();
		testScene.renderScene();
		//testModel->RenderModel();
		//testMesh.RenderMesh();
		shaderTest->Unbind();

		//testScene.setModel("testModel", glm::vec3(0.0f, x, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}
	testTexture.Unbind();
	glfwTerminate();
	return 0;
}