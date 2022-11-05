#pragma once

namespace PE {
	class Renderable {
	public:
		virtual void render() = 0;

	private:
		friend class Application;
	};
}