#pragma once

#include "Component.h"
#include "Transform.h"

#include <vector>

namespace PE {
	//Game objects have a transform associated with them and are able to be instantiated
	class GameObject {
	public:
		void addComponent(Component* component);

		Transform* getTransform();
	private:
		void onStart();
		void update();
		void onDestroy();

		friend class Application;

		std::vector<Component*> _components;
		bool _initialized;
		Transform _transform;
		
	};
}