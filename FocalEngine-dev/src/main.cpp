#include "window.h"
#include "inputManager.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "game/gui.h"

/* Singletons */
Window* Window::s_instance = nullptr;
InputManager* InputManager::s_instance = nullptr;

int main()	
{
	/* Initialization of Engine Here */
	if (!glfwInit()) return -1;

	/* Engine Related Code Here */
	Window::createInstance("mainWindow", 800, 600, false);
	InputManager::createInstance();
	Window* mainWindow = Window::getInstance();

	/* Game Related Code Here */
	GUI gui("Default");
	Shader testShader("Test", "/res/shader/basic.frag", "/res/shader/basic.vert");
	
	std::vector<Vertex> test_vertices;
	test_vertices.push_back( { glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) } );
	test_vertices.push_back({ glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	test_vertices.push_back({ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f) });

	std::vector<unsigned int> test_indices;
	test_indices.push_back(0);
	test_indices.push_back(1);
	test_indices.push_back(2);

	Mesh testMesh(test_vertices, test_indices);

	Texture testTexture("/res/texture/error.png");
	testTexture.LoadTexture();

	/* Render Loop */
	while (mainWindow->renderLoop())
	{
		testShader.Bind();
		testTexture.Bind();
		testMesh.RenderMesh();
		testTexture.Unbind();
		testShader.Unbind();
	}

	glfwTerminate();
	return 0;
}