#pragma once
#include <vendor/NixTools/system.h>
#include <vendor/glm/glm.hpp>
#include "inputManager.h"
#include "core/coreGUI.h"

class Camera : public NixTools::System, KeyboardInput, MouseInput, CoreGUIListener
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
	bool m_Fclicked, m_EscClicked;
	double xChange, yChange;
	double lastX, lastY;
	float sensivity;
	float m_cameraVelocity;
public:
	Camera(std::string componentName, glm::vec3 cameraPosition, glm::vec2 rotation);

	void update();
	glm::mat4 calculateViewMatrix();

	void keyControl();
	void mouseControl();

	glm::vec3 getPosition() { return m_position; }

	void keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouseEvents(GLFWwindow* window, double xPos, double yPos);

	void onEscClicked(bool* EscClicked) override;
};