#include "core/GameObject.h"

using namespace PE;

PE::GameObject::GameObject() : _initialized(false),
_transform(),
_deltaTime(0.0f)
{
	//link transform to this
	_transform._gameObject = this;
}

void PE::GameObject::onStart()
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i].get()->onStart();
	}

	_initialized = true;
}

void PE::GameObject::update()
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i].get()->_deltaTime = _deltaTime;
		_components[i].get()->update();
	}
}

void PE::GameObject::onDestroy()
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i].get()->onDestroy();
	}
}

void PE::GameObject::onGUI()
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i].get()->onGUI();
	}
}

Transform* PE::GameObject::getTransform()
{
	return &_transform;
}