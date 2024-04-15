#include "lights/directionalLight.h"

DirectionalLight::DirectionalLight(std::string lightName, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float intensity)
	:CoreLight(lightName, color, position, intensity), m_direction(direction)
{
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
}

void DirectionalLight::useLight()
{
	m_mainShader->SetUniform3f("directionalLight.color", m_lightColor.x, m_lightColor.y, m_lightColor.z);
	m_mainShader->SetUniform3f("directionalLight.direction", m_direction.x, m_direction.y, m_direction.z);
	m_mainShader->SetUniform1f("directionalLight.intensity", m_lightIntensity);
}

void DirectionalLight::stopLight()
{
	m_mainShader->SetUniform1f("directionalLight.intensity", 0.0f);
}

