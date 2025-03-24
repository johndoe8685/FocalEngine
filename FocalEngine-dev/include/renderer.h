#pragma once
#include <vendor/NixTools/system.h>
#include "shaderManager.h"
#include "scene.h"

class Renderer : public NixTools::System
{
private:
	ShaderManager* m_shaderManager;
public:
	void renderModel(Model* model);
	void renderScene(Scene* scene);
};