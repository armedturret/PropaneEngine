#version 460 core
in vec2 uvCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 ambient;
uniform vec4 color;
uniform sampler2D diffuseTex0;

struct PointLight{
	vec3 color;
	vec3 pos;
};

uniform int numLights;

uniform PointLight pointLights[32];

vec3 calcPointLight(PointLight light, vec3 norm)
{
	vec3 lightDir = normalize(light.pos - fragPos);  
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 256);

	vec3 result = diff * light.color;
	result += spec * light.color;
	return result;
}

void main()
{
	vec3 norm = normalize(normal);

	vec4 result = texture(diffuseTex0, uvCoord) * vec4(ambient, 1.0);
	for(int i = 0; i < numLights; i++)
	{
		result += vec4(calcPointLight(pointLights[i], norm), 0.0);
	}
	result *= color;
	FragColor = result;
}