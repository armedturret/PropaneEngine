#pragma once

#include "core/components/Camera.h"
#include "render/LightingData.h"

namespace PE {
	struct RenderContext {
		Camera* camera;
		LightingData* lightingData;
	};
}