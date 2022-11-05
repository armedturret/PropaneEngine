#pragma once

#include "Renderable.h"

#include "Shader.h"

namespace PE {
	class Model : public Renderable {
	public:
		void init() override;
		void render() override;
		void cleanUp() override;

	private:
		unsigned int _vbo;

		Shader _shader;
	};
}