#pragma once

#include "core/components/Camera.h"

namespace PE {
	class Renderable {
	public:
		Renderable();

		virtual void render(Camera* camera) = 0;

	private:
		friend class Application;
	};
}