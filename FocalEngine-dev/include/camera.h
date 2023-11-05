#pragma once
#include <vendor/NixTools/system.h>
#include <vendor/glm/glm.hpp>
#include "inputManager.h"

class Camera : public NixTools::System, KeyboardInput, MouseInput
{
private:
	//TODO: Add Projection Modes into the Camera
	enum ProjectionMode
	{
		Perspective,
		Orthographic
	};
	ProjectionMode m_mode;

	glm::vec3 m_position;
	glm::vec2 m_rotation;
	glm::vec3 m_direction;
	glm::vec3 front, up, right;

	bool keys[1024];
	bool Fclicked;
	double xChange, yChange;
	double lastX, lastY;
	float sensivity;
public:
	Camera(std::string componentName, glm::vec3 cameraPosition, glm::vec2 rotation);

	void update();
	glm::mat4 calculateViewMatrix();

	void keyControl();
	void mouseControl();

	void keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouseEvents(GLFWwindow* window, double xPos, double yPos);
};