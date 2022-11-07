#pragma once

#include "core/Component.h"

namespace PE {
	class NoclipController : public Component {
	public:
		NoclipController();

		void onStart() override;
		void update() override;
		void onDestroy() override;

		void setSpeed(float amount);
		void setSensitivity(glm::vec2 sensitivity);

	private:
		float _speed;
		glm::vec2 _sensitivity;
	};
}