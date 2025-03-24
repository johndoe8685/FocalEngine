#version 330 core
out vec4 FragColor;

in vec3 FragmentPosition;

uniform float elapsedTime;


void main()
{
	vec2 coord = gl_FragCoord.xy * 0.015;
	coord += elapsedTime * 2;

	
	int xCheck = int(floor(coord.x)) % 2;
	int yCheck = int(floor(coord.y)) % 2;

	if(xCheck == yCheck) 
	{
		FragColor = vec4(1.0, 0.647, 0.0, 1.0); // Orange
		//FragColor = vec4(1.0, 0.0, 1.0, 1.0); //Error Pink
	}
	else
	{
		FragColor = vec4(0.0); // Black
		//FragColor = vec4(1.0); // White
	}
}