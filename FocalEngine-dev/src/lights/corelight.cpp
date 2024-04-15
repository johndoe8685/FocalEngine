#include "lights/corelight.h"

CoreLight::CoreLight(std::string lightName, glm::vec3 lightColor, glm::vec3 lightPosition, float lightIntensity)
	:System(lightName, "Light"), m_lightColor(lightColor), m_lightPosition(lightPosition), m_lightIntensity(lightIntensity)
{
	ShaderManager* manager = ShaderManager::getInstance();
	m_mainShader = manager->getShader("MainShader");
}


