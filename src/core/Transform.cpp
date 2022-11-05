#include "core/Transform.h"

PE::Transform::Transform():
	_position(0.0f),
	_rotation(),
	_scale(1.0f)
{

}

glm::vec3 PE::Transform::getPosition() const
{
	return _position;
}

void PE::Transform::setPosition(glm::vec3 newPos)
{
	_position = newPos;
}

glm::vec3 PE::Transform::getScale() const
{
	return _scale;
}

void PE::Transform::setScale(glm::vec3 scale)
{
	_scale = scale;
}

glm::quat PE::Transform::getRotation() const
{
	return _rotation;
}

void PE::Transform::setRotation(glm::quat rotation) {
	_rotation = rotation;
}