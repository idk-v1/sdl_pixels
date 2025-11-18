#include <SDL3/SDL.h>
#include <stdio.h>

//#define USE_AVX
#include "graphics.h"

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	Uint32 width = 600, height = 600;

	SDL_Window* window = SDL_CreateWindow("SDL Test", width, height, SDL_WINDOW_RESIZABLE);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	pixFmt = SDL_GetPixelFormatDetails(surface->format);


	float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	Uint64 timer = SDL_GetTicks();
	Uint32 fps = 0;

	bool running = true; 
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_EVENT_QUIT:
				running = false;
				break;

			case SDL_EVENT_WINDOW_RESIZED:
				surface = SDL_GetWindowSurface(window);
				width = surface->w;
				height = surface->h;
				break;
			}
		}
		SDL_GetMouseState(&mouseX, &mouseY);

		Uint64 now = SDL_GetTicks();
		Uint32 fpsScale = 1;
		if (now - timer >= 1000 / fpsScale)
		{
			timer = now;
			char title[50];
			snprintf(title, 50, "SDL Test | %u x %u | %u fps", width, height, fps * fpsScale);
			SDL_SetWindowTitle(window, title);
			fps = 0;
		}

		clearScreen(surface, rgb(0x00, 0x00, 0x3F));

		drawCircle(surface, mouseX, mouseY, 100, rgb(255, 255, 255));

		drawText(surface, 10, 100, 0, rgb(255, 255, 255), "'<': signed/\nunsigned mismatch");
		drawText(surface, 10, 125, 1, rgb(255, 255, 255), "'<': signed/\nunsigned mismatch");
		drawText(surface, 10, 175, 2, rgb(255, 255, 255), "'<': signed/\nunsigned mismatch");
		drawText(surface, 10, 250, 3, rgb(255, 255, 255), "'<': signed/\nunsigned mismatch");
		
		SDL_UpdateWindowSurface(window);
		fps++;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}