#pragma once

#include "render/components/Light.h"

#include <vector>

namespace PE {
	struct LightingData {
		const static size_t MAX_LIGHTS = 32;

		std::vector<Light*> lights;
		Color ambient = WHITE;
	};
}