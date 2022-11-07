#version 460 core
in vec3 vertPos;
in vec2 uvPos;

out vec2 uvCoord;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(vertPos.x, vertPos.y, vertPos.z, 1.0);
	uvCoord = uvPos;
}