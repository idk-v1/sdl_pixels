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

Uint32 colors[10];

void drawKey(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 w, Uint32 h, Uint32 fontSize, const char* key, Uint64 ticks)
{
	static int count = 0;
	count++;
	drawRectA(surface, x, y, 0, 0, w, h, rgb(0x00, 0x00, 0x00));
	drawTextA(surface, x, y, 0, 0, fontSize, colors[(ticks / 2 + x / 50 + y / 50) % 10], key);
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	Uint32 width = 1000, height = 600;

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

		{
			Sint32 keyWR = 40;
			Sint32 keyHR = 40;
			Sint32 keyWF = 35;
			Sint32 keyHF = 24;
			Sint32 keyWN = 35;
			Sint32 keyHN = 40;

			Sint32 x = 30;
			Sint32 y = 200;
			Sint32 pad = 5;

			drawRect(surface, x - pad, y - pad, 815, 259, rgb(0x07, 0x07, 0x07));
			x = 50;
			y += 12;

			drawKey(surface, x, y, keyWR, keyHF, 0, "Esc", ticks);   x += (keyWR + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F1", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F2", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F3", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F4", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F5", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F6", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F7", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F8", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F9", ticks);    x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F10", ticks);   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F11", ticks);   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F12", ticks);   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "PrtSc", ticks); x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "Ins", ticks);   x += (keyWR + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHF, 0, "Del", ticks);   x += (keyWR + keyWF) / 2 + pad + 2;
			drawKey(surface, x, y, keyWF, keyHF, 0, "Home", ticks);  x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "End", ticks);   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "PgUp", ticks);  x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "PgDn", ticks);
			x = 50;
			y += (keyHF + keyHR) / 2 + pad;

			drawKey(surface, x, y, keyWR, keyHR, 1, "~\n`", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "!\n1", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "@\n2", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "#\n3", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "$\n4", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "%\n5", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "^\n6", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "&\n7", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "*\n8", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "(\n9", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, ")\n0", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "_\n-", ticks);                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "+\n=", ticks);                 x += (keyWR +    60) / 2 + pad;
			drawKey(surface, x, y,    60, keyHR, 0, "       <-\nBackspace", ticks); x += (keyWN +    60) / 2 + pad + 1;
			drawKey(surface, x, y, keyWN, keyHN, 0, "Num\nLock", ticks);            x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "/", ticks);                    x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "*", ticks);                    x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "-", ticks);
			x = 50 + 40 / 2 / 2;
			y += (keyHR + keyHR) / 2 + pad;
			
			drawKey(surface, x, y,    60, keyHR, 0, "Tab", ticks);    x += (keyWR +   60) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "Q", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "W", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "E", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "R", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "T", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "Y", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "U", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "I", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "O", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "P", ticks);      x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "{\n[", ticks);   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "}\n]", ticks);   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "|\n\\", ticks);  x += (keyWR + keyWN) / 2 + pad + 1;
			drawKey(surface, x, y, keyWN, keyHN, 1, "7", ticks);      x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "8", ticks);      x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "9", ticks);      x += (keyWN + keyWN) / 2 + pad; y += keyHN / 2 + pad / 2 + 1;
			drawKey(surface, x, y, keyWN, keyHN * 2 + pad, 1, "\n+", ticks);
			x = 50 + 60 / 2 / 2;
			y -= keyHN / 2 + pad / 2 + 1;
			y += (keyHR + keyHR) / 2 + pad;

			drawKey(surface, x, y,    70, keyHR, 0, "Capslock", ticks); x += (keyWR +    70) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "A", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "S", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "D", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "F", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "G", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "H", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "J", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "K", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "L", ticks);        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, ":\n;", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "\"\n'", ticks);    x += (keyWR +    75) / 2 + pad + 1;
			drawKey(surface, x, y,    75, keyHR, 0, "Enter", ticks);    x += (keyWN +    75) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "4", ticks);        x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "5", ticks);        x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "6", ticks);        x += (keyWN + keyWN) / 2 + pad;
			x = 50 + 110 / 2 / 2;
			y += (keyHR + keyHR) / 2 + pad;

			drawKey(surface, x, y,    95, keyHR, 0, "Shift", ticks); x += (keyWR +    95) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "Z", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "X", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "C", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "V", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "B", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "N", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "M", ticks);     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "<\n,", ticks);  x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, ">\n.", ticks);  x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "?\n/", ticks);  x += (keyWR +    56) / 2 + pad;
			drawKey(surface, x, y,    56, keyHR, 0, "Shift", ticks); x += (keyWN +    56) / 2 + pad + 1;
			drawKey(surface, x, y, keyWN, keyHN, 0, "/\\", ticks);   x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "1", ticks);     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "2", ticks);     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "3", ticks);     x += (keyWN + keyWN) / 2 + pad; y += keyHN / 2 + pad / 2 + 1;
			drawKey(surface, x, y, keyWN, keyHN * 2 + pad, 0, "\nEnter", ticks);
			x = 50 + 20 / 2 / 2;
			y -= keyHN / 2 + pad / 2 + 1;
			y += (keyHR + keyHR) / 2 + pad;

			drawKey(surface, x, y,    50, keyHR, 0, "Ctrl", ticks);  x += (keyWR +    50) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Fn", ticks);    x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Win", ticks);   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Alt", ticks);   x += (keyWR +   225) / 2 + pad + 1;
			drawKey(surface, x, y,   225, keyHR, 0, "", ticks);      x += (keyWR +   225) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Alt", ticks);   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Menu", ticks);  x += (keyWR +    55) / 2 + pad + 1;
			drawKey(surface, x, y,    55, keyHR, 0, "Ctrl", ticks);  x += (keyWN +    55) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "<", ticks);     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 0, "\\/", ticks);   x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, ">", ticks);     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "0", ticks);     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, ".", ticks);     x += (keyWN + keyWN) / 2 + pad;
		}

		Uint32 textW, textH;

		// Info display
		getTextSizeF(1, &textW, &textH, "FPS       (%11u)", fps);
		drawRect(surface, 10, 10, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 10, 1, rgb(0xFF, 0xFF, 0xFF), "FPS       (%11u)", fps);

		getTextSizeF(1, &textW, &textH, "Size      (%5d %5d)", width, height);
		drawRect(surface, 10, 30, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 30, 1, rgb(0xFF, 0xFF, 0xFF), "Size      (%5d %5d)", width, height);

		getTextSizeF(1, &textW, &textH, "Position  (%+5d %+5d)", mouseX - mouseXR, mouseY - mouseYR);
		drawRect(surface, 10, 50, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 50, 1, rgb(0xFF, 0xFF, 0xFF), "Position  (%+5d %+5d)", mouseX - mouseXR, mouseY - mouseYR);

		getTextSizeF(1, &textW, &textH, "Mouse     (%+5d %+5d)", mouseX, mouseY);
		drawRect(surface, 10, 70, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 70, 1, rgb(0xFF, 0xFF, 0xFF), "Mouse     (%+5d %+5d)", mouseX, mouseY);

		getTextSizeF(1, &textW, &textH, "Mouse Rel (%+5d %+5d)", mouseXR, mouseYR);
		drawRect(surface, 10, 90, textW, textH, rgb(0x00, 0x00, 0x00));
		drawTextF(surface, 10, 90, 1, rgb(0xFF, 0xFF, 0xFF), "Mouse Rel (%+5d %+5d)", mouseXR, mouseYR);
		
		drawRectOutA(surface, mouseXR, mouseYR, 0, 0, 200, 200, 5, rgb(0xFF, 0x00, 0x00));

		SDL_UpdateWindowSurface(window);
		fpsCount++;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}