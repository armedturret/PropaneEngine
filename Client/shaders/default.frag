#version 460 core
in vec2 uvCoord;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D diffuseTex0;

void main()
{
	FragColor = texture(diffuseTex0, uvCoord) * color;
}