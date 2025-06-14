#pragma once

#include <SDL3/SDL_events.h>

namespace ks {
	class Window;

	struct State {
		State() = default;
		virtual ~State() = default;

		virtual auto on_event(SDL_Event& event) = 0;
		virtual auto input() = 0;
		virtual auto update(const float dt) = 0;
		virtual auto draw(ks::Window& window) = 0;
	};
}