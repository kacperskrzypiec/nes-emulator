#include "App.hpp"

#include <iostream>
#include <format>

#define DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char* argv[]) {
	doctest::Context ctx;
	ctx.setOption("abort-after", 5);
	ctx.applyCommandLine(argc, argv);
	ctx.setOption("no-breaks", true);
	ctx.run();
	CHECK(1 == 1);


	SDL_Init(SDL_INIT_VIDEO);

	try {
		ks::App app;
		app.run();
	}
	catch (std::exception& e) {
		std::cerr << std::format("ERROR: {}\n", e.what());
	}

	SDL_Quit();
}