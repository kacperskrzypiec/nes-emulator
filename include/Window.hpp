#pragma once

#include <SDL3/SDL.h>

namespace ks {
	class Window {
	public:
		Window() = default;
		~Window() {
			if (m_renderer) {
				SDL_DestroyRenderer(m_renderer);
			}
			if (m_window) {
				SDL_DestroyWindow(m_window);
			}
		}

		auto create(const char* title, const int width, const int height, SDL_WindowFlags flags) -> bool {
			if (SDL_CreateWindowAndRenderer(title, width, height, flags, &m_window, &m_renderer)) {
				m_size = { width, height };
				m_isOpen = 1;
				return 1;
			}

			return 0;
		}

		auto on_event(SDL_Event& event) -> void {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				close();
				break;
			case SDL_EVENT_WINDOW_RESIZED:
				m_size.x = event.window.data1;
				m_size.y = event.window.data2;
				break;
			default:
				break;
			}
		}

		auto close() -> void {
			m_isOpen = 0;
		}
		auto is_open() const -> bool {
			return m_isOpen;
		}

		auto get_size() const -> SDL_Point {
			return m_size;
		}

		auto get_window() -> SDL_Window* {
			return m_window;
		}
		auto get_renderer() -> SDL_Renderer* {
			return m_renderer;
		}
		operator SDL_Window*() {
			return m_window;
		}
		operator SDL_Renderer* () {
			return m_renderer;
		}

	private:
		SDL_Window* m_window{};
		SDL_Renderer* m_renderer{};

		SDL_Point m_size{};

		bool m_isOpen{};
	};
}