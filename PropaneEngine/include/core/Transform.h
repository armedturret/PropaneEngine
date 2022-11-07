#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

namespace PE {
	class Transform {
	public:
		Transform();

		glm::vec3 getPosition() const;
		void setPosition(glm::vec3 newPos);

		glm::vec3 getScale() const;
		void setScale(glm::vec3 scale);

		glm::quat getRotation() const;
		void setRotation(glm::quat rotation);

		//gets the normalized forward vector in terms of the world (standard is X+)
		glm::vec3 getForward() const;
		//gets the normalized right vector in terms of the world (standarad is Z+)
		glm::vec3 getRight() const;
		//gets the normalized up vector in terms of the world (standard is Y+)
		glm::vec3 getUp() const;
	private:
		glm::vec3 _position;
		glm::vec3 _scale;
		glm::quat _rotation;
	};
}