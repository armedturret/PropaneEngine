#include "core/Transform.h"

#include "core/GameObject.h"

#include <glm/gtx/matrix_decompose.hpp>

PE::Transform::Transform() :
	_position(0.0f),
	_rotation(glm::vec3(0.0f)),
	_scale(1.0f),
	_parent(nullptr),
	_gameObject(nullptr),
	_localPosition(0.0f),
	_localRotation(glm::vec3(0.0f)),
	_localScale(1.0f),
	_transform(1.0f),
	_dirty(false)
{

}

glm::vec3 PE::Transform::getPosition() const
{
	return _position;
}

void PE::Transform::setPosition(glm::vec3 newPos)
{
	if (_parent != nullptr)
		_localPosition = glm::inverse(_parent->getTransformMatrix()) * glm::vec4(newPos, 1.0f);
	else
		_localPosition = newPos;

	updatePositionInternal(newPos);
}

glm::vec3 PE::Transform::getScale() const
{
	return _scale;
}

void PE::Transform::setScale(glm::vec3 scale)
{
	if (scale.x == 0.0f)
		scale.x = 0.00000001f;
	if (scale.y == 0.0f)
		scale.y = 0.00000001f;
	if (scale.z == 0.0f)
		scale.z = 0.00000001f;

	if (_parent != nullptr)
		_localScale = glm::scale(glm::mat4(1.0f), 1.0f / _parent->getScale()) * glm::vec4(scale, 1.0f);
	else
		_localScale = scale;

	updateScaleInternal(scale);
}

glm::quat PE::Transform::getRotation() const
{
	return _rotation;
}

void PE::Transform::setRotation(glm::quat rotation)
{
	if (_parent != nullptr)
		_localRotation = glm::inverse(_parent->_rotation) * rotation;
	else
		_localRotation = rotation;

	updateRotationInternal(rotation);
}

glm::vec3 PE::Transform::getLocalPosition() const
{
	return _localPosition;
}

void PE::Transform::setLocalPosition(glm::vec3 newPos)
{
	_localPosition = newPos;
	updatePositionInternal(_parent->getTransformMatrix()* glm::vec4(newPos, 1.0f));
}

glm::vec3 PE::Transform::getLocalScale() const
{
	return _localScale;
}

void PE::Transform::setLocalScale(glm::vec3 scale)
{
	if (scale.x == 0.0f)
		scale.x = 0.00000001f;
	if (scale.y == 0.0f)
		scale.y = 0.00000001f;
	if (scale.z == 0.0f)
		scale.z = 0.00000001f;

	_localScale = scale;
	updateScaleInternal(glm::scale(glm::mat4(1.0f), _parent->getScale()) * glm::vec4(scale, 1.0f));
}

glm::quat PE::Transform::getLocalRotation() const
{
	return _localRotation;
}

void PE::Transform::setLocalRotation(glm::quat rotation)
{
	_localRotation = rotation;
	updateRotationInternal(_parent->getRotation() * rotation);
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
	//recalculate transform matrix
	if (_dirty)
	{
		_transform = glm::translate(glm::mat4(1.0f), _position);
		_transform *= glm::toMat4(_rotation);
		_transform = glm::scale(_transform, _scale);
		_dirty = false;
	}

	return _transform;
}

void PE::Transform::setRelativeTransformMatrix(glm::mat4 transform)
{
	//decompose the transform into local position, rotation, and scale
	glm::vec3 translation;
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transform, scale, rotation, translation, skew, perspective);
	setLocalPosition(translation);
	setLocalScale(scale);
	setLocalRotation(glm::quat(rotation));
}

void PE::Transform::setParent(Transform* parent)
{
	if (parent == this)
		throw "Attempted to assign self as parent";
	//remove self from parent
	if (_parent != nullptr && _parent->indexOfChild(this) != -1)
	{
		int index = _parent->indexOfChild(this);
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

void PE::Transform::updatePositionInternal(glm::vec3 newPos)
{
	_position = newPos;
	_dirty = true;

	for (auto child : _children)
		child->setLocalPosition(child->getLocalPosition());
}

void PE::Transform::updateScaleInternal(glm::vec3 scale)
{
	_scale = scale;
	_dirty = true;

	for (auto child : _children)
	{
		child->setLocalScale(child->getLocalScale());
		child->setLocalPosition(child->getLocalPosition());
	}
}

void PE::Transform::updateRotationInternal(glm::quat rotation)
{
	_rotation = rotation;
	_dirty = true;

	for (auto child : _children)
	{
		child->setLocalRotation(child->getLocalRotation());
		child->setLocalPosition(child->getLocalPosition());
	}
}

int PE::Transform::indexOfChild(Transform* child)
{
	for (int i = 0; i < _children.size(); i++)
	{
		Transform* compareChild = _children[i];
		if (compareChild == child)
			return i;
	}

	return -1;
}