#version 460 core
in vec3 vertPos;
in vec3 norm;
in vec2 texCoord;

out vec2 uvCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vertPos, 1.0);
	fragPos = (model * vec4(vertPos, 1.0)).xyz;
	normal = norm;
	uvCoord = texCoord;
}