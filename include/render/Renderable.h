#pragma once

namespace PE {
	class Renderable {
	public:
		Renderable();
		
		virtual void render() = 0;

	private:
		friend class Application;
	};
}