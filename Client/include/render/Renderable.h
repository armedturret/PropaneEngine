#pragma once

#include "core/components/Camera.h"

#include "render/RenderContext.h"

namespace PE {
	class Renderable {
	public:
		Renderable();

		virtual void render(RenderContext* context) = 0;

	private:
		friend class Application;
	};
}