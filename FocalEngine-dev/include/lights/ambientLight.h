#pragma once
#include "lights/corelight.h"

class AmbientLight : public CoreLight
{
public:
	AmbientLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity);

	void useLight();
	void stopLight();
};