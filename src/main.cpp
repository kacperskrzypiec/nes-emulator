#include "App.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <iostream>
#include <format>

int main(int argc, char* argv[]) {
	// Run tests (disabled in production build)
	doctest::Context ctx;
	ctx.applyCommandLine(argc, argv);
	ctx.setOption("abort-after", 5);
	ctx.setOption("no-breaks", true);
	ctx.run();

	// Run the application
	SDL_Init(SDL_INIT_VIDEO);

	try {
		ks::App app;
		app.run();
	} catch (const std::runtime_error& e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Runtime Error", e.what(), nullptr);
	} catch (const std::exception& e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", e.what(), nullptr);
	}

	SDL_Quit();
}