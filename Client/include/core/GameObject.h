#pragma once

#include "Component.h"
#include "Transform.h"

#include <string>
#include <vector>
#include <unordered_set>
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

		template <class T>
		std::vector<std::shared_ptr<T>>
			getComponents()
		{
			std::vector<std::shared_ptr<T>> _foundComponents;
			for (auto comp : _components)
			{
				if (dynamic_cast<T*>(comp.get()) != nullptr)
				{
					_foundComponents.push_back(comp);
				}
			}

			return _foundComponents;
		}

		template <class T>
		std::shared_ptr<T>
			getComponent()
		{
			std::vector<std::shared_ptr<T>> _foundComponents;
			for (auto comp : _components)
			{
				if (dynamic_cast<T*>(comp.get()) != nullptr)
				{
					return comp;
				}
			}

			return nullptr;
		}

		GameObject();

		GameObject* findChildByName(std::string name);

		std::vector<GameObject*> getChildren();
		Transform* getTransform();

		std::string getName();
		void setName(std::string nam);
	private:
		void onStart();
		void update(float deltaTime);
		void onDestroy();
		void onGUI();

		friend class Application;

		std::vector<std::shared_ptr<Component>> _components;
		std::string _name;
		bool _initialized;
		Transform _transform;
	};
}