#include "core/GameObject.h"

using namespace PE;

void PE::GameObject::onStart() 
{

}

void PE::GameObject::update() 
{

}

void PE::GameObject::onDestroy() 
{

}

void PE::GameObject::addComponent(Component* component)
{
	_components.push_back(component);
}

Transform* PE::GameObject::getTransform() 
{
	return &_transform;
}