#include <SDL3/SDL.h>
#include <stdio.h>

#define USE_SSE
#include "graphics.h"

void getMousePos(Sint32* mouseX, Sint32* mouseY)
{
	float x = 0, y = 0;
	SDL_GetGlobalMouseState(&x, &y);
	*mouseX = x;
	*mouseY = y;
}

void getMousePosRel(SDL_Window* window, Sint32* mouseX, Sint32* mouseY)
{
	Sint32 mx, my;
	getMousePos(&mx, &my);
	Sint32 winX, winY;
	SDL_GetWindowPosition(window, &winX, &winY);
	*mouseX = mx - winX;
	*mouseY = my - winY;
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	Uint32 width = 600, height = 600;

	SDL_Window* window = SDL_CreateWindow("SDL Test", width, height, SDL_WINDOW_RESIZABLE);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	pixFmt = SDL_GetPixelFormatDetails(surface->format);

	Sint32 mouseX, mouseY;
	Sint32 mouseXR, mouseYR;

	Uint64 lastTime = SDL_GetTicks();
	Uint64 deltaTime = 0;
	Uint64 ups = 30;
	Uint64 lastFPSTime = SDL_GetTicks();
	Uint32 fpsCount = 0;
	Uint32 fps = 0;

	Uint64 ticks = 0;

	Uint32 colors[10];
	colors[0] = rgb(0xFF, 0x00, 0x00);
	colors[1] = rgb(0xFF, 0x7F, 0x00);
	colors[2] = rgb(0xFF, 0xFF, 0x00);
	colors[3] = rgb(0x00, 0xFF, 0x00);
	colors[4] = rgb(0x00, 0xFF, 0xFF);
	colors[5] = rgb(0x00, 0x7F, 0xFF);
	colors[6] = rgb(0x00, 0x00, 0xFF);
	colors[7] = rgb(0x7F, 0x00, 0xFF);
	colors[8] = rgb(0xFF, 0x00, 0xFF);
	colors[9] = rgb(0xFF, 0x00, 0x7F);

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
		getMousePos(&mouseX, &mouseY);
		getMousePosRel(window, &mouseXR, &mouseYR);

		Uint64 now = SDL_GetTicks();

		deltaTime += now - lastTime;
		while (deltaTime >= 1000 / ups)
		{
			deltaTime -= 1000 / ups;
			ticks++;
		}
		lastTime = now;

		Uint32 fpsScale = 1;
		if (now - lastFPSTime >= 1000 / fpsScale)
		{
			lastFPSTime = now;
			fps = fpsCount * fpsScale;
			fpsCount = 0;
		}

		clearScreen(surface, rgb(0x00, 0x00, 0x3F));

		Uint32 textW, textH;		
		
		
		// basically drawText, but rainbow
		Sint32 textX = 0;
		Sint32 textY = 0;
		for (Sint32 i = ' ' + 1; i < 127; i++)
		{
			drawChar(surface, 10 + textX, 275 + textY, 2, colors[9 - (ticks / 2 + textX / font_w / 2 + textY / font_h / 2) % 10], i);
			if ((i - ' ') % 24 == 0 && (i - ' '))
			{
				textY += font_h * 2;
				textX = 0;
			}
			else
			{
				textX += font_w * 2;
			}
		}

		// Info display
		getTextSizeF(1, &textW, &textH, "FPS       (%11u)", fps);
		drawRect(surface, 10, 0, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 0, 1, rgb(0xFF, 0xFF, 0xFF), "FPS       (%11u)", fps);

		getTextSizeF(1, &textW, &textH, "Size      (%5d %5d)", width, height);
		drawRect(surface, 10, 20, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 20, 1, rgb(0xFF, 0xFF, 0xFF), "Size      (%5d %5d)", width, height);

		getTextSizeF(1, &textW, &textH, "Position  (%+5d %+5d)", mouseX - mouseXR, mouseY - mouseYR);
		drawRect(surface, 10, 40, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 40, 1, rgb(0xFF, 0xFF, 0xFF), "Position  (%+5d %+5d)", mouseX - mouseXR, mouseY - mouseYR);

		getTextSizeF(1, &textW, &textH, "Mouse     (%+5d %+5d)", mouseX, mouseY);
		drawRect(surface, 10, 60, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 60, 1, rgb(0xFF, 0xFF, 0xFF), "Mouse     (%+5d %+5d)", mouseX, mouseY);

		getTextSizeF(1, &textW, &textH, "Mouse Rel (%+5d %+5d)", mouseXR, mouseYR);
		drawRect(surface, 10, 80, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 80, 1, rgb(0xFF, 0xFF, 0xFF), "Mouse Rel (%+5d %+5d)", mouseXR, mouseYR);
		

		SDL_UpdateWindowSurface(window);
		fpsCount++;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}