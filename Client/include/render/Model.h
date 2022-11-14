#pragma once

#include "core/GameObject.h"
#include "render/Mesh.h"
#include "render/Material.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct aiNode;

namespace PE {
	
	class Model {
	public:
		void loadFromFile(std::string modelFile);

		void setMaterials(std::vector<std::shared_ptr<Material>> materials);

		int getRequiredMaterialCount();

		GameObject* createInstance();

	private:
		struct Node {
			std::vector<unsigned int> targetMeshes;
			std::vector<Node> children;
			std::string name;
			glm::mat4 transform;
		};

		struct VertexInfluences {
			std::vector<int> boneIndices;
			std::vector<float> weights;
		};

		Node convertNode(aiNode* assimpNode);

		GameObject* createObjectFromNode(Node* node, GameObject* root);

		std::vector<Mesh> _meshes;
		std::vector<std::shared_ptr<Material>> _materials;
		Node _rootNode;
		int _requiredMaterialCount;
	};
}