#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normal;

uniform mat4 mvp;
uniform mat4 model;
uniform float elapsedTime;
uniform float wanted_fps;

out vec2 TextureCoordinates;
out vec3 Normal;
out vec3 FragmentPosition;
out vec3 CameraPosition;

void main()
{
/*
    //Check if we should render this frame
    bool isRender = false;
    int section_index = int(elapsedTime / wanted_fps);

    if(section_index % 2 == 0)
    {
        shouldRender = 0.0;
    }
    else
    {
        shouldRender = 1.0;
    }
	*/
    
	gl_Position = mvp * vec4(position, 1.0);
    TextureCoordinates = textureCoordinates;
    Normal = mat3(transpose(inverse(model))) * normal;
    FragmentPosition = vec3(model * vec4(position, 1.0));
}