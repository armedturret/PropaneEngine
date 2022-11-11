#include "render/components/Light.h"

#include "Application.h"

PE::Light::Light():
	_color(WHITE),
	_type(TYPE::POINT)
{
	Application::getInstance().getRenderer().getLightingData()->lights.push_back(this);
}

void PE::Light::setLight(TYPE type, Color color)
{
	_type = type;
	_color = color;
}