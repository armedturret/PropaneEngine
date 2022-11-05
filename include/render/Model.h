#pragma once

#include "Renderable.h"

#include "Shader.h"

namespace PE {
	class Model : public Renderable {
	public:
		Model(bool drawStatic = false);

		void init() override;
		void render() override;
		void cleanUp() override;

	private:
		bool _drawStatic;

		unsigned int _vbo, _vao;

		Shader _shader;
	};
}