#include "core/components/Camera.h"

#include "Application.h"

void PE::Camera::onStart()
{
	_ortho = false;
	_fov = 45.0f;
	_nearPlane = 0.001f;
	_farPlane = 1000.f;
	_orthoSize = 1.0f;

	//set this to default camera if non exists
	if (Application::getInstance().getRenderer().getCamera() == nullptr)
		Application::getInstance().getRenderer().setCamera(this);
}

void PE::Camera::update()
{

}

void PE::Camera::onDestroy()
{

}

glm::mat4 PE::Camera::getProjectionMatrix()
{
	glm::ivec2 dimensions = Application::getInstance().getDimensions();
	float aspect = (float)dimensions[0] / (float)dimensions[1];

	if (!_ortho)
	{
		return glm::perspective(_fov, aspect, _nearPlane, _farPlane);
	}
	else
	{
		return glm::ortho(-_orthoSize * aspect, _orthoSize * aspect, -_orthoSize, _orthoSize);
	}
}

glm::mat4 PE::Camera::getLookMatrix()
{
	//uses camera pos, target pos (forward), and up direction
	return glm::lookAt(getTransform()->getPosition(),
		getTransform()->getForward(),
		getTransform()->getUp());
}

float PE::Camera::getFov() const
{
	return _fov;
}

void PE::Camera::setFov(float fov)
{
	_fov = fov;
}

float PE::Camera::getNearPlane() const
{
	return _nearPlane;
}

void PE::Camera::setNearPlane(float val)
{
	_nearPlane = val;
}

float PE::Camera::getFarPlane() const
{
	return _farPlane;
}

void PE::Camera::setFarPlane(float val)
{
	_farPlane = val;
}

float PE::Camera::getOrthoSize() const
{
	return _orthoSize;
}

void PE::Camera::setOrthoSize(float val)
{
	_orthoSize = val;
}

bool PE::Camera::isOrtho() const
{
	return _ortho;
}

void PE::Camera::setOrtho(bool val)
{
	_ortho = val;
}