#include "render/Renderer.h"

#include <glm/glm.hpp>
#include <gl/glew.h>
using namespace glm;

#include <iostream>

void PE::Renderer::initialize()
{
	std::cout << "Initializing renderer" << std::endl;

	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		throw "GLEW failed to initialize";
	}

	//solid black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//cull backfaces to reduce render time
	glCullFace(GL_BACK);

	//create a test model for now
	_renderables.push_back(&_model);

	//initalize all renderables
	for (auto renderable : _renderables) {
		renderable->init();
	}
}

void PE::Renderer::render()
{
	//clear window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render all renderables
	for (auto renderable : _renderables) {
		renderable->render();
	}
}

void PE::Renderer::cleanUp()
{
	std::cout << "Closing renderer" << std::endl;
	for (auto renderable : _renderables) {
		renderable->cleanUp();
	}
}
