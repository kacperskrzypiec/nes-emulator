#pragma once

#include "Window.hpp"
#include "NES/RP2A03.hpp"
#include "NES/Bus.hpp"

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
		ks::Bus m_bus;
		ks::RP2A03 m_cpu;
	};
}