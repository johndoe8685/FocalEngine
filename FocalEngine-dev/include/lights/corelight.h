#pragma once
#include <vendor/NixTools/system.h>
#include <vendor/glm/glm.hpp>
#include "shaderManager.h"

class CoreLight : public NixTools::System
{
protected:
	glm::vec3 m_lightColor;
	glm::vec3 m_lightPosition;
	float m_lightIntensity;

	Shader* m_mainShader;
public:
	CoreLight(std::string lightName, glm::vec3 lightColor, glm::vec3 lightPosition, float lightIntensity);
	virtual void useLight() = 0;
	virtual void stopLight() = 0;
};