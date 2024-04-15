#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normal;

uniform mat4 mvp;
uniform mat4 model;

out vec2 TextureCoordinates;
out vec3 Normal;
out vec3 FragmentPosition;
out vec3 CameraPosition;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    TextureCoordinates = textureCoordinates;
    Normal = mat3(transpose(inverse(model))) * normal;
    FragmentPosition = vec3(model * vec4(position, 1.0));
}