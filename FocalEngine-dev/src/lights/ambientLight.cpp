#include "lights/ambientLight.h"

AmbientLight::AmbientLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity)
	:CoreLight(lightName, color, position, intensity)
{
}

void AmbientLight::useLight()
{
	m_mainShader->SetUniform3f("ambientLight.color", m_lightColor.x, m_lightColor.y, m_lightColor.z);
	m_mainShader->SetUniform1f("ambientLight.intensity", m_lightIntensity);
}

void AmbientLight::stopLight()
{
	m_mainShader->SetUniform1f("ambientLight.intensity", 0.0f);
}
