#include "camera.h"
#include "shaderManager.h"
#include <sstream>

Camera::Camera(std::string componentName, glm::vec3 cameraPosition, glm::vec2 rotation)
	:System(componentName, "Camera"), m_position(cameraPosition), m_rotation(rotation), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), sensivity(0.2f), Fclicked(false)
{
	KeyboardInput* keyboardInput = static_cast<KeyboardInput*>(this);
	InputManager::getInstance()->addInput(keyboardInput);

	MouseInput* mouseInput = static_cast<MouseInput*>(this);
	InputManager::getInstance()->addInput(mouseInput);
}

void Camera::update()
{
	keyControl();
	mouseControl();

	front.x = cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
	front.y = sin(glm::radians(m_rotation.y));
	front.z = sin(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(m_position, m_position + front, up);
}

void Camera::keyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if(!Fclicked) 
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Fclicked = true;
		}
		else 
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			Fclicked = false;
		}
	}
	

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void Camera::keyControl()
{
	if (keys[GLFW_KEY_G]) debugger.giveMessage(NixTools::Debugger::Error, "Fuck you");
	
	if (Fclicked)
	{
		ShaderManager* shaderManager = ShaderManager::getInstance();

		float velocity = 5.0f * shaderManager->getDeltatime();

		if (keys[GLFW_KEY_W])
		{
			m_position += front * velocity;
		}

		if (keys[GLFW_KEY_S])
		{
			m_position -= front * velocity;
		}

		if (keys[GLFW_KEY_A])
		{
			m_position -= glm::normalize(glm::cross(front, up)) * velocity;
		}

		if (keys[GLFW_KEY_D])
		{
			m_position += glm::normalize(glm::cross(front, up)) * velocity;
		}
	}
}

void Camera::mouseEvents(GLFWwindow* window, double xPos, double yPos)
{
	xChange = xPos - lastX;
	yChange = lastY - yPos;

	lastX = xPos;
	lastY = yPos;
}

void Camera::mouseControl()
{
	if (Fclicked)
	{
		xChange = xChange * sensivity;
		yChange = yChange * sensivity;

		m_rotation.x += xChange;
		m_rotation.y += yChange;

		xChange = 0;
		yChange = 0;

		if (m_rotation.y > 89.0f)
		{
			m_rotation.y = 89.0f;
		}

		if (m_rotation.y < -89.0f)
		{
			m_rotation.y = -89.0f;
		}
	}
}


