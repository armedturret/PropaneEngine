#include "core/Transform.h"

PE::Transform::Transform() :
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

void PE::Transform::setRotation(glm::quat rotation)
{
	_rotation = rotation;
}

glm::vec3 PE::Transform::getForward() const
{
	return glm::normalize(glm::rotate(_rotation, glm::vec3(1.0f, 0.0f, 0.0f)));
}

glm::vec3 PE::Transform::getUp() const
{
	return glm::normalize(glm::cross(getRight(), getForward()));
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