#pragma once

#include "render/Renderable.h"
#include "render/Material.h"
#include "render/Mesh.h"
#include "core/Component.h"

#include <memory>
#include <vector>

namespace PE {
	class MeshRenderer : public Renderable, public Component {
	public:
		MeshRenderer();

		void setMesh(Mesh mesh);
		void setMaterial(std::shared_ptr<Material> material);
		void setArmatureRoot(Transform* root);

		void onStart() override;
		void render(RenderContext* context) override;
		void update() override;
		void onDestroy() override;
	private:
		//struct used for updating bone data from hierarchy
		struct BoneData {
			std::string name;
			Transform* transform;
			glm::mat4 lastTransform;
		};

		void reloadData();
		
		//updates bone transforms
		void updateBones();

		//updates the meta data of the bones to include references
		void updateBoneInfo();

		unsigned int _vbo, _vao, _ebo;

		bool _buffersCreated;

		std::vector<BoneData> _bonesInfo;
		std::vector<glm::mat4> _boneTransforms;
		Transform* _armatureRoot;
		std::shared_ptr<Material> _material;
		Mesh _mesh;
	};
}