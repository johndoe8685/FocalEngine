#version 330 core
in vec2 TexCoord;
uniform sampler2D aTexture;

out vec4 FragColor;

void main()
{
    FragColor = texture(aTexture, TexCoord);
}