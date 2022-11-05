#pragma once

#include <vector>

#include "Renderable.h"
#include "Model.h"

namespace PE {
	class Renderer {
	public:
		void initialize();
		void render();
		void cleanUp();
		void addRenderable(Renderable* renderable);
	private:
		std::vector<Renderable*> _renderables;

		Model _model;
	};
}