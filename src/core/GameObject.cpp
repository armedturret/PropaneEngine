#include "core/GameObject.h"

using namespace PE;

void PE::GameObject::onStart() 
{
	for (int i = 0; i < _components.size(); i++) {
		_components[i].get()->onStart();
	}

	_initialized = true;
}

void PE::GameObject::update() 
{
	for (int i = 0; i < _components.size(); i++) {
		_components[i].get()->update();
	}
}

void PE::GameObject::onDestroy() 
{
	for (int i = 0; i < _components.size(); i++) {
		_components[i].get()->onDestroy();
	}
}

PE::GameObject::GameObject(): _initialized(false),
_transform()
{

}

Transform* PE::GameObject::getTransform() 
{
	return &_transform;
}