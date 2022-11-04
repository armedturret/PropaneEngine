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

	//give it the color of blood
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void PE::Renderer::render()
{
	//render all renderables
	for (auto renderable : _renderables) {
		renderable->render();
	}

	//clear window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PE::Renderer::cleanUp()
{
	std::cout << "Closing renderer" << std::endl;
}
