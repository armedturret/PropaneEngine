#pragma once

#include "Transform.h"

namespace PE {
	//components lack a transform, instead inheriting from their parent game object (think camera, model, etc)
	class Component {
	public:
		virtual void onStart() = 0;
		virtual void update() = 0;
		virtual void onDestroy() = 0;

		Transform* getTransform() const { return _parentTransform; }

	private:
		friend class GameObject;
		Transform* _parentTransform;
	};
}