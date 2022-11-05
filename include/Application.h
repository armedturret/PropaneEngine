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
		static Application& getInstance() {
			static Application instance;

			return instance;
		}

		int run(int argc, char** argv);
		
		//creates a duplicate of the game object, adding it to the game objects list
		GameObject* createGameObject();

		~Application();

		Renderer* getRenderer();
		
		Application(Application const&) = delete;
		void operator=(Application const&) = delete;
	private:
		Application();

		//window stuff
		GLFWwindow* _window;

		std::vector<std::shared_ptr<GameObject>> _gameObjects;

		Renderer _renderer;
		bool _initialized;
	};
}