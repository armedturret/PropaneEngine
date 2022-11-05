#pragma once

#include "render/Renderable.h"
#include "render/Shader.h"
#include "core/Component.h"

namespace PE {
	class Model : public Renderable, public Component{
	public:
		Model();

		void onStart() override;
		void render() override;
		void update() override;
		void onDestroy() override;

	private:
		bool _drawStatic;

		unsigned int _vbo, _vao;

		Transform _transform;
		Shader _shader;
	};
}