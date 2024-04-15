#pragma once
#include "lights/corelight.h"
#include <sstream>
#define MAX_POINT_LIGHT 32

class PointLight : public CoreLight
{
private:
	std::stringstream stream;

	std::string colorName;
	std::string positionName;
	std::string intensityName;
	std::string inUseName;
	
	static int m_pointLightIndex;
public:
	PointLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity);

	void useLight();
	void stopLight();
};