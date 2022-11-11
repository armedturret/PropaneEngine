#version 460 core
in vec2 uvCoord;

out vec4 FragColor;

uniform vec3 ambient;
uniform vec4 color;
uniform sampler2D diffuseTex0;

void main()
{
	FragColor = texture(diffuseTex0, uvCoord) * color * vec4(ambient, 1.0);
}