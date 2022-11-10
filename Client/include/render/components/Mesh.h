#pragma once

#include "render/Renderable.h"
#include "render/Material.h"
#include "core/Component.h"

#include <memory>
#include <vector>

namespace PE {
	class Mesh : public Renderable, public Component {
	public:
		struct Vertex {
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texCoord;
		};

		Mesh();

		void setVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		void useMaterial(std::shared_ptr<Material> material);

		void onStart() override;
		void render(Camera* camera) override;
		void update() override;
		void onDestroy() override;
	private:
		void reloadData();

		unsigned int _vbo, _vao, _ebo;

		bool _buffersCreated;

		std::shared_ptr<Material> _material;
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
	};
}