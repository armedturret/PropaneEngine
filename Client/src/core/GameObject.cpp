#include "core/GameObject.h"

using namespace PE;

PE::GameObject::GameObject() : _initialized(false),
_transform(),
_name("GameObject")
{
	//link transform to this
	_transform._gameObject = this;
}

GameObject* PE::GameObject::findChildByName(std::string name)
{
	//check children
	for (auto child : getChildren())
	{
		//check if it is a match
		if (child->_name == name)
			return child;

		//check child's children
		GameObject* result = child->findChildByName(name);
		if (result != nullptr)
			return result;
	}

	//none found
	return nullptr;
}

std::string PE::GameObject::getName()
{
	return _name;
}

void PE::GameObject::setName(std::string name)
{
	_name = name;
}

void PE::GameObject::onStart()
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i]->onStart();
	}

	_initialized = true;

	auto children = getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->onStart();
	}
}

void PE::GameObject::update(float deltaTime)
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i]->_deltaTime = deltaTime;
		_components[i]->update();
	}

	auto children = getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->update(deltaTime);
	}
}

void PE::GameObject::onDestroy()
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i]->onDestroy();
	}

	auto children = getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->onDestroy();
	}
}

void PE::GameObject::onGUI()
{
	for (int i = 0; i < _components.size(); i++)
	{
		_components[i]->onGUI();
	}

	auto children = getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->onGUI();
	}
}

std::vector<GameObject*> PE::GameObject::getChildren()
{
	return _transform._objectChildren;
}

Transform* PE::GameObject::getTransform()
{
	return &_transform;
}