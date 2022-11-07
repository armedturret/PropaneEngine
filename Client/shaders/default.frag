#version 460 core
in vec2 uvCoord;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D diffuseTex;

void main()
{
	FragColor = texture(diffuseTex, uvCoord) * color;
}