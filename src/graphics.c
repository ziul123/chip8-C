#include "SDL2/SDL.h"

#include "graphics.h"
#include "global.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700

#define COLOR(R,G,B,A) (R), (G), (B), (A)

SDL_Renderer *renderer;
SDL_Window *window;

void init_window() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderPresent(renderer);
}

void update_window() {
	for (int row = 0; row <= SCREEN_HEIGHT; row++) {
		for (int col = 0; col <= SCREEN_WIDTH; col++) {
			if (screen[row * SCREEN_WIDTH + col])
				SDL_SetRenderDrawColor(renderer, COLOR(255,255,255,255));
			else
				SDL_SetRenderDrawColor(renderer, COLOR(0,0,0,255));
			SDL_RenderDrawPoint(renderer, col, row);
		}
	}

	SDL_RenderPresent(renderer);
}

void destroy_window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
