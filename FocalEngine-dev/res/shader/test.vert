#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 mvp;
uniform mat4 model;

out vec3 FragmentPosition;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);
	FragmentPosition = vec3(model * vec4(position, 1.0));
}