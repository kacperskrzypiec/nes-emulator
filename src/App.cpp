#include "App.hpp"
#include "NES/Register.hpp"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <iostream>
#include <format>

namespace ks {
	App::App() {
		m_window.create("NES emulator", 1280, 720, SDL_WINDOW_RESIZABLE);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.LogFilename = nullptr;
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_window);
		ImGui_ImplSDLRenderer3_Init(m_window);
	}
	App::~App() {
		ImGui_ImplSDLRenderer3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}

	auto App::run() -> void {
		uint64_t lastTime{};

		while (m_window.is_open()) {
			const uint64_t start = SDL_GetTicksNS();
			handle_events();

			const float deltaTime = (SDL_GetTicksNS() - lastTime) / 1E9f;
			lastTime = SDL_GetTicksNS();

			input(deltaTime);
			update(deltaTime);
			draw();

			const uint64_t delay = 1'000'000'000ULL / 60 - (SDL_GetTicksNS() - start);
			if (delay > 0) {
				SDL_DelayPrecise(delay);
			}
		}
	}

	auto App::handle_events() -> void {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			m_window.on_event(event);
		}
	}
	auto App::input(const float dt) -> void {

	}
	auto App::update(const float dt) -> void {
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Window");
		if (ImGui::Button("Cycle")) {
			m_cpu.cycle();
		}
		ImGui::Text(std::format("X: {}", m_cpu.get_state().X).c_str());
		ImGui::End();
	}
	auto App::draw() -> void {
		SDL_RenderClear(m_window);

		
		ImGui::Render();
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_window);
		SDL_SetRenderDrawColor(m_window, 0, 0, 0, 255);
		SDL_RenderPresent(m_window);
	}
}