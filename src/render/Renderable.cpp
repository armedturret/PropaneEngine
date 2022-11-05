#include "render/Renderable.h"

#include "Application.h"

#include <iostream>

PE::Renderable::Renderable() {
	Application::getInstance().getRenderer()->addRenderable(this);
}