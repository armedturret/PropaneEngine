#version 460 core
in vec3 pos;
in vec3 norm;
in vec2 texCoord;
in ivec4 boneIds;
in vec4 weights;

out vec2 uvCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 bones[MAX_BONES];

void main()
{
	
	//accumulate bone influences (first check if any influences EXIST)
	vec4 totalPosition = vec4(0.0f);
	if(boneIds[0] == -1)
		totalPosition = vec4(pos, 1.0f);

	//add bone influence
	for(int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		if(boneIds[i] == -1)
			continue;
		if(boneIds[i] >= MAX_BONES)
		{
			totalPosition = vec4(pos, 1.0f);
			break;
		}
		vec4 localPosition = bones[boneIds[i]] * vec4(pos,1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(bones[boneIds[i]]) * norm;
	}

	gl_Position = projection * view * model * totalPosition;

	//variable passing
	fragPos = (model * totalPosition).xyz;
	normal = mat3(transpose(inverse(model))) * norm;
	uvCoord = texCoord;
}