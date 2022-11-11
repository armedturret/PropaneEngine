#include "core/Transform.h"

#include "core/GameObject.h"

PE::Transform::Transform() :
	_position(0.0f),
	_rotation(glm::vec3(0.0f)),
	_scale(1.0f),
	_parent(nullptr),
	_gameObject(nullptr),
	_localPosition(0.0f),
	_localRotation(glm::vec3(0.0f)),
	_localScale(1.0f)
{

}

glm::vec3 PE::Transform::getPosition() const
{
	return _position;
}

void PE::Transform::setPosition(glm::vec3 newPos)
{
	_position = newPos;

	if (_parent != nullptr)
		_localPosition = glm::inverse(_parent->getTransformMatrix()) * glm::vec4(_position, 1.0f);
	else
		_localPosition = _position;

	for (auto child : _children)
		child->setLocalPosition(child->getLocalPosition());
}

glm::vec3 PE::Transform::getScale() const
{
	return _scale;
}

void PE::Transform::setScale(glm::vec3 scale)
{
	if (scale == glm::vec3(0.0f))
		scale = glm::vec3(0.00000000001f);

	_scale = scale;

	if (_parent != nullptr)
		_localScale = glm::scale(glm::mat4(1.0f), 1.0f / _parent->getScale()) * glm::vec4(_scale, 1.0f);
	else
		_localScale = _scale;

	for (auto child : _children)
		child->setLocalScale(child->getLocalScale());
}

glm::quat PE::Transform::getRotation() const
{
	return _rotation;
}

void PE::Transform::setRotation(glm::quat rotation)
{
	_rotation = rotation;

	if (_parent != nullptr)
		_localRotation = glm::inverse(_parent->_rotation) * _rotation;
	else
		_localRotation = _rotation;

	for (auto child : _children)
		child->setLocalRotation(child->getLocalRotation());
}

glm::vec3 PE::Transform::getLocalPosition() const
{
	return _localPosition;
}

void PE::Transform::setLocalPosition(glm::vec3 newPos)
{
	setPosition(_parent->getTransformMatrix()* glm::vec4(newPos, 1.0f));
}

glm::vec3 PE::Transform::getLocalScale() const
{
	return _localScale;
}

void PE::Transform::setLocalScale(glm::vec3 scale)
{
	if (scale == glm::vec3(0.0f))
		scale = glm::vec3(0.00000000001f);

	//update local position as well since this is affected
	setLocalPosition(_localPosition);
	setScale(glm::scale(glm::mat4(1.0f), _parent->getScale()) * glm::vec4(scale, 1.0f));
}

glm::quat PE::Transform::getLocalRotation() const
{
	return _localRotation;
}

void PE::Transform::setLocalRotation(glm::quat rotation)
{
	//update local position as well since this is affected
	setLocalPosition(_localPosition);
	setRotation(_parent->getRotation() * rotation);
}

glm::vec3 PE::Transform::getForward() const
{
	return glm::normalize(glm::rotate(_rotation, glm::vec3(1.0f, 0.0f, 0.0f)));
}

glm::vec3 PE::Transform::getUp() const
{
	return glm::normalize(glm::rotate(_rotation, glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 PE::Transform::getRight() const
{
	return glm::normalize(glm::rotate(_rotation, glm::vec3(0.0f, 0.0f, 1.0f)));
}

glm::vec3 PE::Transform::getBackward() const
{
	return -getForward();
}

glm::vec3 PE::Transform::getDown() const
{
	return -getUp();
}

glm::vec3 PE::Transform::getLeft() const
{
	return -getRight();
}

glm::mat4 PE::Transform::getTransformMatrix()
{
	return glm::translate(glm::mat4(1.0f), _position)
		* glm::toMat4(_rotation)
		* glm::scale(glm::mat4(1.0f), _scale);
}

void PE::Transform::setParent(Transform* parent)
{
	if (parent == this)
		throw "Attempted to assign self as parent";
	//remove self from parent
	if (_parent != nullptr && _parent->indexOfChild(this) != -1)
	{
		int index = _parent->indexOfChild(this) != -1;
		_parent->_children.erase(_parent->_children.begin() + index);
		_parent->_objectChildren.erase(_parent->_objectChildren.begin() + index);
	}

	//set the other to be this parent
	_parent = parent;

	//update local transforms
	setPosition(_position);
	setRotation(_rotation);
	setScale(_scale);

	//add self to parent
	if (_parent != nullptr)
	{
		_parent->_children.push_back(this);
		_parent->_objectChildren.push_back(_gameObject);
	}
}

PE::GameObject* PE::Transform::getGameObject() const
{
	return _gameObject;
}

PE::Transform* PE::Transform::getParent()
{
	return _parent;
}

std::vector<PE::Transform*> PE::Transform::getChildren()
{
	return _children;
}

int PE::Transform::indexOfChild(Transform* child)
{
	for (int i = 0; i < _children.size(); i++)
	{
		if (_children[i] == child)
			return i;
	}

	return -1;
}