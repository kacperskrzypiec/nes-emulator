#include <SDL3/SDL.h>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("NES Emulator - build test", 512, 480, 0);
	SDL_Delay(1000);
	SDL_DestroyWindow(window);
	SDL_Quit();
}