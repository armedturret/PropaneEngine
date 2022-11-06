#pragma once

#include <vector>

namespace PE {
	class Material {
		static void freeMaterials();

	private:
		static std::vector<Material&> _materials;
	};
}