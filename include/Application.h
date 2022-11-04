#pragma once

#include "render/Renderer.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace PE {
	class Application {
	public:
		int run(int argc, char** argv);

		~Application();
	private:
		//window stuff
		GLFWwindow* _window;

		Renderer _renderer;
		bool _quit;
	};
}