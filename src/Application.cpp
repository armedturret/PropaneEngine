#include "Application.h"

int PE::Application::run(int argc, char** argv)
{
	//create the window
	if (!glfwInit()) {
		throw "Failed to initialize glfw";
	}

	//if I wanted to have antialising, using glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //open gl version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); //forward compatiblity
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //use modern opengl

	_window = glfwCreateWindow(640, 480, "Skeggy 3 Real??????!?!?", NULL, NULL);
	if (!_window) {
		throw "Window failed to initialize";
	}

	glfwMakeContextCurrent(_window);
	
	_renderer.initialize();

	while (!glfwWindowShouldClose(_window)) {
		//call render pass
		_renderer.render();

		//swap buffers to prevent flickering
		glfwSwapBuffers(_window);

		//check for input and the like
		glfwPollEvents();
	}

	//don't bother with clean up since called out of scope
}

PE::Application::~Application()
{
	_renderer.cleanUp();
	glfwTerminate();
}
