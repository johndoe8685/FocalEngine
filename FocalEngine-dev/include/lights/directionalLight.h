#pragma once
#include "lights/corelight.h"

class DirectionalLight : public CoreLight
{
private:
	std::string colorName = "directionalLight.color";
	std::string positionName = "directionalLight.position";
	std::string directionName = "directionalLight.direction";
	std::string intensityName = "directionalLight.intensity";
	glm::vec3 m_direction;
public:
	DirectionalLight(std::string lightName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float intensity);
	
	void setDirection(glm::vec3 direction);

	void useLight();
	void stopLight();
};