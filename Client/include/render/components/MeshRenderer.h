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

		void onStart() override;
		void render(Camera* camera) override;
		void update() override;
		void onDestroy() override;
	private:
		void reloadData();

		unsigned int _vbo, _vao, _ebo;

		bool _buffersCreated;

		std::shared_ptr<Material> _material;
		Mesh _mesh;
	};
}