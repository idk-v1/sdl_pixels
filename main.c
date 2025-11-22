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

void drawKey(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 w, Uint32 h, Uint32 fontSize, const char* key)
{
	drawRectA(surface, x, y, 0, 0, w, h, rgb(0x0F, 0x0F, 0x0F));
	drawTextA(surface, x, y, 0, 0, fontSize, rgb(0xFF, 0xFF, 0xFF), key);
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
		//Sint32 textX = 0;
		//Sint32 textY = 0;
		//for (Sint32 i = ' ' + 1; i < 127; i++)
		//{
		//	drawChar(surface, 10 + textX, 275 + textY, 2, colors[9 - (ticks / 2 + textX / font_w / 2 + textY / font_h / 2) % 10], i);
		//	if ((i - ' ') % 24 == 0 && (i - ' '))
		//	{
		//		textY += font_h * 2;
		//		textX = 0;
		//	}
		//	else
		//	{
		//		textX += font_w * 2;
		//	}
		//}

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

			drawRect(surface, x - pad, y - pad, 815, 259, rgb(0x00, 0x00, 0x00));
			x = 50;
			y += 12;

			drawKey(surface, x, y, keyWR, keyHF, 0, "Esc");  x += (keyWR + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F1");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F2");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F3");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F4");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F5");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F6");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F7");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F8");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F9");   x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F10");  x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F11");  x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "F12");  x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "Prt");  x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "Ins");  x += (keyWR + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHF, 0, "Del");  x += (keyWR + keyWF) / 2 + pad + 2;
			drawKey(surface, x, y, keyWF, keyHF, 0, "Home"); x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "End");  x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "PgUp"); x += (keyWF + keyWF) / 2 + pad;
			drawKey(surface, x, y, keyWF, keyHF, 0, "PgDn");
			x = 50;
			y += (keyHF + keyHR) / 2 + pad;

			drawKey(surface, x, y, keyWR, keyHR, 1, "~\n`");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "!\n1");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "@\n2");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "#\n3");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "$\n4");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "%\n5");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "^\n6");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "&\n7");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "*\n8");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "(\n9");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, ")\n0");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "_\n-");                 x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "+\n=");                 x += (keyWR +    60) / 2 + pad;
			drawKey(surface, x, y,    60, keyHR, 0, "       <-\nBackspace"); x += (keyWN +    60) / 2 + pad + 1;
			drawKey(surface, x, y, keyWN, keyHN, 0, "Num\nLock");            x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "/");                    x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "*");                    x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "-");
			x = 50 + 40 / 2 / 2;
			y += (keyHR + keyHR) / 2 + pad;
			
			drawKey(surface, x, y,    60, keyHR, 0, "Tab"); x += (keyWR +   60) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "Q");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "W");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "E");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "R");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "T");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "Y");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "U");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "I");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "O");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "P");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "[");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "]");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "\\");  x += (keyWR + keyWN) / 2 + pad + 1;
			drawKey(surface, x, y, keyWN, keyHN, 1, "7");   x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "8");   x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "9");   x += (keyWN + keyWN) / 2 + pad; y += keyHN / 2 + pad / 2 + 1;
			drawKey(surface, x, y, keyWN, keyHN * 2 + pad, 1, "\n+");
			x = 50 + 60 / 2 / 2;
			y -= keyHN / 2 + pad / 2 + 1;
			y += (keyHR + keyHR) / 2 + pad;

			drawKey(surface, x, y,    70, keyHR, 0, "Capslock"); x += (keyWR +    70) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "A");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "S");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "D");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "F");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "G");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "H");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "J");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "K");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "L");        x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, ":\n;");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "\"\n'");    x += (keyWR +    75) / 2 + pad + 1;
			drawKey(surface, x, y,    75, keyHR, 0, "Enter");    x += (keyWN +    75) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "4");        x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "5");        x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "6");        x += (keyWN + keyWN) / 2 + pad;
			x = 50 + 110 / 2 / 2;
			y += (keyHR + keyHR) / 2 + pad;

			drawKey(surface, x, y,    95, keyHR, 0, "Shift"); x += (keyWR +    95) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "Z");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "X");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "C");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "V");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "B");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "N");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "M");     x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "<\n,");  x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, ">\n.");  x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 1, "?\n/");  x += (keyWR +    56) / 2 + pad;
			drawKey(surface, x, y,    56, keyHR, 0, "Shift"); x += (keyWN +    56) / 2 + pad + 1;
			drawKey(surface, x, y, keyWN, keyHN, 0, "/\\");   x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "1");     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "2");     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "3");     x += (keyWN + keyWN) / 2 + pad; y += keyHN / 2 + pad / 2 + 1;
			drawKey(surface, x, y, keyWN, keyHN * 2 + pad, 0, "\nEnter");
			x = 50 + 20 / 2 / 2;
			y -= keyHN / 2 + pad / 2 + 1;
			y += (keyHR + keyHR) / 2 + pad;

			drawKey(surface, x, y,    50, keyHR, 0, "Ctrl");  x += (keyWR +    50) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Fn");    x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Win");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Alt");   x += (keyWR +   225) / 2 + pad + 1;
			drawKey(surface, x, y,   225, keyHR, 0, "");      x += (keyWR +   225) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Alt");   x += (keyWR + keyWR) / 2 + pad;
			drawKey(surface, x, y, keyWR, keyHR, 0, "Menu");  x += (keyWR +    55) / 2 + pad + 1;
			drawKey(surface, x, y,    55, keyHR, 0, "Ctrl");  x += (keyWN +    55) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "<");     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 0, "\\/");   x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, ">");     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, "0");     x += (keyWN + keyWN) / 2 + pad;
			drawKey(surface, x, y, keyWN, keyHN, 1, ".");     x += (keyWN + keyWN) / 2 + pad;
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