#pragma once

#include "Component.h"
#include "Transform.h"

#include <vector>

namespace PE {
	//Game objects have a transform associated with them and are able to be instantiated
	class GameObject {
	public:
		virtual void onStart();
		virtual void update();
		virtual void onDestroy();

		void addComponent(Component* component);

		Transform* getTransform();
	private:
		friend class Application;

		std::vector<Component*> _components;
		Transform _transform;
		
	};
}