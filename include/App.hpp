#pragma once

#include "Window.hpp"

#include <SDL3/SDL.h>

namespace ks {
	class App {
	public:
		App();
		~App();

		auto run() -> void;

	private:
		auto handle_events() -> void;
		auto input(const float dt) -> void;
		auto update(const float dt) -> void;
		auto draw() -> void;

	private:
		ks::Window m_window;
	};
}