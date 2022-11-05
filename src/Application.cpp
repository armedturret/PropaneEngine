#include "Application.h"

#include "render/components/Model.h"

int PE::Application::run(int argc, char** argv)
{
	//temporarily create a game object with a model
	GameObject g;
	Model m;
	g.addComponent(&m);
	createGameObject(g);

	//create the window
	if (!glfwInit()) {
		throw "Failed to initialize glfw";
	}

	//if I wanted to have antialising, using glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //open gl version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); //forward compatiblity
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //use modern opengl
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //do not allow window resizing

	_window = glfwCreateWindow(640, 480, "Skeggy 3 Real??????!?!?", NULL, NULL);
	if (!_window) {
		throw "Window failed to initialize";
	}

	glfwMakeContextCurrent(_window);
	
	_renderer.initialize();

	//initialize all game objects
	for (int i = 0; i < _gameObjects.size(); i++) {
		_gameObjects[i].get()->onStart();
	}

	_initialized = true;

	while (!glfwWindowShouldClose(_window)) {
		//game object updates
		for (int i = 0; i < _gameObjects.size(); i++) {
			_gameObjects[i].get()->update();
		}

		//call render pass
		_renderer.render();

		//swap buffers to prevent flickering
		glfwSwapBuffers(_window);

		//check for input and the like
		glfwPollEvents();
	}

	//don't bother with clean up since called out of scope
	return 0;
}

void PE::Application::createGameObject(GameObject base) {
	//create a unique pointer from the base
	std::unique_ptr<GameObject> temp(new GameObject(base));
	
	//check if any of its child components are renderables
	for (auto comp : temp.get()->_components) {
		if (Renderable* r = dynamic_cast<Renderable*>(comp)) {
			_renderer.addRenderable(r);
		}
	}

	if (_initialized)
		temp.get()->onStart();

	//add to the list
	_gameObjects.push_back(std::move(temp));
}

PE::Application::~Application()
{
	for (int i = 0; i < _gameObjects.size(); i++) {
		_gameObjects[i].get()->onDestroy();
	}

	_renderer.cleanUp();
	glfwTerminate();
}
