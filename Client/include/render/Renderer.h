#pragma once

#include <vector>

#include "Renderable.h"
#include "LightingData.h"

namespace PE {
	class Camera;
	class Light;

	class Renderer {
	public:
		void initialize();
		void render();
		void cleanUp();
		void addRenderable(Renderable* renderable);
		void removeRenderable(Renderable* renderable);

		LightingData* getLightingData();

		Camera* getCamera() const;
		void setCamera(Camera* camera);
	private:
		std::vector<Renderable*> _renderables;
		
		LightingData _lightingData;
		Camera* _camera;
	};
}