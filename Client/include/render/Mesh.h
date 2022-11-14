#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace PE {
	//only 4 verts cann affect any bone
	const int MAX_BONE_INFLUENCE = 4;

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;

		int boneIds[MAX_BONE_INFLUENCE];
		float boneWeights[MAX_BONE_INFLUENCE];
	};

	struct Bone {
		std::string name;
	};

	struct Mesh {
		std::vector<Bone> bones;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		unsigned int modelMaterialIndex; //not required for rendering but used by the model to determine what material should be assigned to this mesh
	};
}
