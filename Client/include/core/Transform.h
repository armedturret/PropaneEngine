#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <unordered_set>
#include <memory>

namespace PE {
	class GameObject;

	class Transform {
	public:
		Transform();

		glm::vec3 getPosition() const;
		void setPosition(glm::vec3 newPos);

		glm::vec3 getScale() const;
		void setScale(glm::vec3 scale);

		glm::quat getRotation() const;
		void setRotation(glm::quat rotation);

		glm::vec3 getLocalPosition() const;
		void setLocalPosition(glm::vec3 newPos);

		glm::vec3 getLocalScale() const;
		void setLocalScale(glm::vec3 scale);

		glm::quat getLocalRotation() const;
		void setLocalRotation(glm::quat rotation);

		//gets the normalized forward vector in terms of the world (standard is X+)
		glm::vec3 getForward() const;
		//gets the normalized up vector in terms of the world (standard is Y+)
		glm::vec3 getUp() const;
		//gets the normalized right vector in terms of the world (standarad is Z+)
		glm::vec3 getRight() const;
		//gets the normalized back vector in terms of the world (standard is X-)
		glm::vec3 getBackward() const;
		//gets the normalized down vector in terms of the world (standard is Y-)
		glm::vec3 getDown() const;
		//gets the normalized left vector in terms of the world (standard is Z-)
		glm::vec3 getLeft() const;
		
		glm::mat4 getTransformMatrix();

		void setParent(Transform* parent);

		GameObject* getGameObject() const;

		Transform* getParent();
		std::vector<Transform*> getChildren();

	private:
		int indexOfChild(Transform* child);
		friend class GameObject;

		GameObject* _gameObject;
		
		Transform* _parent;
		std::vector<Transform*> _children;
		std::vector<GameObject*> _objectChildren;

		glm::vec3 _position;
		glm::vec3 _scale;
		glm::quat _rotation;

		glm::vec3 _localPosition;
		glm::vec3 _localScale;
		glm::quat _localRotation;
	};
}