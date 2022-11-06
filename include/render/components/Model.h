#pragma once

#include "render/Renderable.h"
#include "render/Material.h"
#include "core/Component.h"

#include <memory>

namespace PE {
	class Model : public Renderable, public Component {
	public:
		Model();

		void loadWithMaterial(std::shared_ptr<Material> material, bool drawStatic = false);

		void onStart() override;
		void render(Camera* camera) override;
		void update() override;
		void onDestroy() override;
	private:
		struct Position {
			float x;
			float y;
			float z;
		};

		struct UV {
			float u;
			float v;
		};

		struct Vertex {
			Position position;
			UV uv;
		};

		bool _drawStatic;

		unsigned int _vbo, _vao;

		std::shared_ptr<Material> _material;
	};
}