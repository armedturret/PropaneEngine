#pragma once

#include "render/Renderer.h"
#include "core/GameObject.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

namespace PE {
	class Application {
	public:
		int run(int argc, char** argv);
		
		//creates a duplicate of the game object, adding it to the game objects list
		void createGameObject(GameObject base);

		~Application();
	private:
		//window stuff
		GLFWwindow* _window;

		std::vector<std::unique_ptr<GameObject>> _gameObjects;

		Renderer _renderer;
		bool _initialized;
	};
}