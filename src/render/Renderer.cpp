#include "render/Renderer.h"

#include "core/components/Camera.h"

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

	//various opengl settings
	glCullFace(GL_BACK); //cull backfaces to reduce render time
	glEnable(GL_DEPTH_TEST); //allow depth testing for 3D
}

void PE::Renderer::render()
{
	//clear window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (_camera == nullptr)
		throw "Attempting to render with no camera";

	//render all renderables
	for (auto renderable : _renderables) {
		renderable->render(_camera);
	}
}

void PE::Renderer::cleanUp()
{
	std::cout << "Closing renderer" << std::endl;
}

void PE::Renderer::addRenderable(Renderable* renderable) 
{
	_renderables.push_back(renderable);
}

void PE::Renderer::setCamera(Camera* camera) 
{
	_camera = camera;
}

PE::Camera* PE::Renderer::getCamera() const
{
	return _camera;
}