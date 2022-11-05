#pragma once

#include "core/Component.h"

namespace PE {
	class Camera : public Component {
	public:
		void onStart() override;
		void update() override;
		void onDestroy() override;

		glm::mat4 getProjectionMatrix();
		glm::mat4 getLookMatrix();

		float getFov() const;
		void setFov(float fov);

		float getNearPlane () const;
		void setNearPlane(float val);

		float getFarPlane() const;
		void setFarPlane(float val);

		float getOrthoSize() const;
		void setOrthoSize(float val);

		bool isOrtho() const;
		void setOrtho(bool val);
	private:
		float _fov;
		float _nearPlane;
		float _farPlane;

		float _orthoSize;
		bool _ortho;
	};
}