#pragma once

#include "Transform.h"

namespace PE {
	class GameObject;

	//components lack a transform, instead inheriting from their parent game object (think camera, model, etc)
	class Component {
	public:
		virtual void onStart() {}
		virtual void update() {}
		virtual void onDestroy() {}

		Transform* getTransform() const { return _transform; }
		GameObject* getGameObject() const { return _gameObject; }

	private:
		friend class GameObject;

		//our component does NOT own these, just referencing
		Transform* _transform;
		GameObject* _gameObject;
	};
}