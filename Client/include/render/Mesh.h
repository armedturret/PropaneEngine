#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace PE {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct VertexWeight {
		unsigned int index;
		float weight;
	};

	struct Bone {
		std::string name;

		std::vector<VertexWeight> vertexWeights;
	};

	struct Mesh {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		unsigned int modelMaterialIndex; //not required for rendering but used by the model to determine what material should be assigned to this mesh
	};
}
