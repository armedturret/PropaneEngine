#include "core/GameObject.h"

using namespace PE;

void PE::GameObject::onStart() 
{
	for (auto comp : _components) {
		comp->onStart();
	}

	_initialized = true;
}

void PE::GameObject::update() 
{
	for (auto comp : _components) {
		comp->update();
	}
}

void PE::GameObject::onDestroy() 
{
	for (auto comp : _components) {
		comp->onDestroy();
	}
}

//this is very bad and allows components to be associated with multiple objects, need to fix later
void PE::GameObject::addComponent(Component* component)
{
	component->_gameObject = this;
	component->_transform = &_transform;

	if (_initialized)
		component->onStart();

	_components.push_back(component);
}

Transform* PE::GameObject::getTransform() 
{
	return &_transform;
}