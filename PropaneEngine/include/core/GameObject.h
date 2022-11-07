#pragma once

#include "Component.h"
#include "Transform.h"

#include <vector>
#include <type_traits>
#include <memory>

namespace PE {
	//Game objects have a transform associated with them and are able to be instantiated
	class GameObject {
	public:
		template <class T>
		typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type
			addComponent()
		{
			std::shared_ptr<Component> temp(new T);
			temp.get()->_gameObject = this;
			temp.get()->_transform = &_transform;

			if (_initialized)
				temp.get()->onStart();

			T* returnVal = (T*)temp.get();

			_components.push_back(std::move(temp));
			return returnVal;
		}

		GameObject();

		Transform* getTransform();
	private:
		void onStart();
		void update();
		void onDestroy();

		friend class Application;

		std::vector<std::shared_ptr<Component>> _components;
		bool _initialized;
		Transform _transform;

	};
}