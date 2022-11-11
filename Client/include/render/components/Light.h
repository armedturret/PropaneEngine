#pragma once

#include <glm/glm.hpp>

#include "render/Color.h"
#include "core/Component.h"

namespace PE {
	class Light : public Component {
	public:
		Light();

		enum TYPE {POINT};

		void setLight(TYPE type, Color color);
	private:
		TYPE _type;
		Color _color;
	};
}