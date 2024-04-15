#include "lights/pointLight.h"

int PointLight::m_pointLightIndex = 0;

PointLight::PointLight(std::string lightName, glm::vec3 color, glm::vec3 position, float intensity)
	:CoreLight(lightName, color, position, intensity)
{
	stream << "pointLights[" << m_pointLightIndex << "].color";
	colorName = stream.str();
	stream.str("");
	
	stream << "pointLights[" << m_pointLightIndex << "].position";
	positionName = stream.str();
	stream.str("");

	stream << "pointLights[" << m_pointLightIndex << "].intensity";
	intensityName = stream.str();
	stream.str("");

	stream << "pointLights[" << m_pointLightIndex << "].inUse";
	inUseName = stream.str();
	stream.str("");

	m_pointLightIndex++;
	m_mainShader->SetUniform1i("pointLightCount", m_pointLightIndex);
}

void PointLight::useLight()
{
	m_mainShader->SetUniform3f(colorName, m_lightColor.x, m_lightColor.y, m_lightColor.z);
	m_mainShader->SetUniform3f(positionName, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);
	m_mainShader->SetUniform1f(intensityName, m_lightIntensity);
	m_mainShader->SetUniform1i(inUseName, true);
}

void PointLight::stopLight()
{
	m_mainShader->SetUniform1i(inUseName, false);
}
