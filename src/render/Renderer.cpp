#include "render/Renderer.h"

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>

void PE::Renderer::initialize()
{
	std::cout << "Initializing renderer" << std::endl;
}

void PE::Renderer::render()
{
	for (auto renderable : _renderables) {
	}
}

void PE::Renderer::cleanUp()
{
	std::cout << "Closing renderer" << std::endl;
}
