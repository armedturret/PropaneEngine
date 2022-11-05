#pragma once

#include <vector>

#include "Renderable.h"

namespace PE {
	class Camera;

	class Renderer {
	public:
		void initialize();
		void render();
		void cleanUp();
		void addRenderable(Renderable* renderable);

		Camera* getCamera() const;
		void setCamera(Camera* camera);
	private:
		std::vector<Renderable*> _renderables;
		
		Camera* _camera;
	};
}