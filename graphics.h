#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static const SDL_PixelFormatDetails* pixFmt = NULL;

inline static Uint32 rgb(Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(pixFmt, NULL, r, g, b);
}

inline static void setPixelUC(SDL_Surface* surface, Uint32 x, Uint32 y, Uint32 color)
{
	((Uint32*)surface->pixels)[x + y * surface->w] = color;
}

inline static void setPixel2UC(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
	*((Uint64*)&((Uint32*)surface->pixels)[x + y * surface->w]) = color;
}

inline static void setPixel(SDL_Surface* surface, Uint32 x, Uint32 y, Uint32 color)
{
	if (x < (Uint32)surface->w && y < (Uint32)surface->h)
		setPixelUC(surface, x, y, color);
	else
		;// printf("Pixel out of bounds (%d %d)\n", x - (Sint32)surface->w, y - (Sint32)surface->h);
}

#ifdef USE_SSE
#if defined(_MSC_VER) && !defined(__clang__)
#define SSE_BEGIN \
    __m128 c128; \
    c128.m128_u32[0] = color; \
    c128.m128_u32[1] = color; \
    c128.m128_u32[2] = color; \
    c128.m128_u32[3] = color;
#else
#define SSE_BEGIN \
    __m128 c128; \
    DECLARE_ALIGNED(Uint32, cccc[4], 16); \
    cccc[0] = color; \
    cccc[1] = color; \
    cccc[2] = color; \
    cccc[3] = color; \
    c128 = *(__m128 *)cccc;
#endif
#endif

#ifdef USE_SSE
inline static void setHLine64(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	// extreme alignment needed to not crash (16 bytes)
	// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_mm_stream_ps&ig_expand=6562
	// make sure caller passes aligned values
	Uint32* pixels = ((Uint32*)surface->pixels + (x + y * surface->w));
	_mm_stream_ps((float*)(pixels +  0), color);
	_mm_stream_ps((float*)(pixels +  4), color);
	_mm_stream_ps((float*)(pixels +  8), color);
	_mm_stream_ps((float*)(pixels + 12), color);
	_mm_stream_ps((float*)(pixels + 16), color);
	_mm_stream_ps((float*)(pixels + 20), color);
	_mm_stream_ps((float*)(pixels + 24), color);
	_mm_stream_ps((float*)(pixels + 28), color);
	_mm_stream_ps((float*)(pixels + 32), color);
	_mm_stream_ps((float*)(pixels + 36), color);
	_mm_stream_ps((float*)(pixels + 40), color);
	_mm_stream_ps((float*)(pixels + 44), color);
	_mm_stream_ps((float*)(pixels + 48), color);
	_mm_stream_ps((float*)(pixels + 52), color);
	_mm_stream_ps((float*)(pixels + 56), color);
	_mm_stream_ps((float*)(pixels + 60), color);
}

inline static void setHLine32(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	Uint32* pixels = &(((Uint32*)surface->pixels)[x + y * surface->w]);
	_mm_stream_ps((float*)(pixels +  0), color);
	_mm_stream_ps((float*)(pixels +  4), color);
	_mm_stream_ps((float*)(pixels +  8), color);
	_mm_stream_ps((float*)(pixels + 12), color);
	_mm_stream_ps((float*)(pixels + 16), color);
	_mm_stream_ps((float*)(pixels + 20), color);
	_mm_stream_ps((float*)(pixels + 24), color);
	_mm_stream_ps((float*)(pixels + 28), color);
}

inline static void setHLine16(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	Uint32* pixels = &(((Uint32*)surface->pixels)[x + y * surface->w]);
	_mm_stream_ps((float*)(pixels +  0), color);
	_mm_stream_ps((float*)(pixels +  4), color);
	_mm_stream_ps((float*)(pixels +  8), color);
	_mm_stream_ps((float*)(pixels + 12), color);
}

inline static void setHLine8(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	Uint32* pixels = &(((Uint32*)surface->pixels)[x + y * surface->w]);
	_mm_stream_ps((float*)(pixels +  0), color);
	_mm_stream_ps((float*)(pixels +  4), color);
}
#else
inline static void setHLine64(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
	//color = 0xFFFF0000FFFF0000;

	setPixel2UC(surface, x + 0, y, color);
	setPixel2UC(surface, x + 2, y, color);
	setPixel2UC(surface, x + 4, y, color);
	setPixel2UC(surface, x + 6, y, color);
	setPixel2UC(surface, x + 8, y, color);
	setPixel2UC(surface, x + 10, y, color);
	setPixel2UC(surface, x + 12, y, color);
	setPixel2UC(surface, x + 14, y, color);
	setPixel2UC(surface, x + 16, y, color);
	setPixel2UC(surface, x + 18, y, color);
	setPixel2UC(surface, x + 20, y, color);
	setPixel2UC(surface, x + 22, y, color);
	setPixel2UC(surface, x + 24, y, color);
	setPixel2UC(surface, x + 26, y, color);
	setPixel2UC(surface, x + 28, y, color);
	setPixel2UC(surface, x + 30, y, color);
	setPixel2UC(surface, x + 32, y, color);
	setPixel2UC(surface, x + 34, y, color);
	setPixel2UC(surface, x + 36, y, color);
	setPixel2UC(surface, x + 38, y, color);
	setPixel2UC(surface, x + 40, y, color);
	setPixel2UC(surface, x + 42, y, color);
	setPixel2UC(surface, x + 44, y, color);
	setPixel2UC(surface, x + 46, y, color);
	setPixel2UC(surface, x + 48, y, color);
	setPixel2UC(surface, x + 50, y, color);
	setPixel2UC(surface, x + 52, y, color);
	setPixel2UC(surface, x + 54, y, color);
	setPixel2UC(surface, x + 56, y, color);
	setPixel2UC(surface, x + 58, y, color);
	setPixel2UC(surface, x + 60, y, color);
	setPixel2UC(surface, x + 62, y, color);

	//setPixelUC(surface, x, y, 0xFFFF00FF);
}

inline static void setHLine32(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
	//color = 0xFFFF7F00FFFF7F00;

	setPixel2UC(surface, x + 0, y, color);
	setPixel2UC(surface, x + 2, y, color);
	setPixel2UC(surface, x + 4, y, color);
	setPixel2UC(surface, x + 6, y, color);
	setPixel2UC(surface, x + 8, y, color);
	setPixel2UC(surface, x + 10, y, color);
	setPixel2UC(surface, x + 12, y, color);
	setPixel2UC(surface, x + 14, y, color);
	setPixel2UC(surface, x + 16, y, color);
	setPixel2UC(surface, x + 18, y, color);
	setPixel2UC(surface, x + 20, y, color);
	setPixel2UC(surface, x + 22, y, color);
	setPixel2UC(surface, x + 24, y, color);
	setPixel2UC(surface, x + 26, y, color);
	setPixel2UC(surface, x + 28, y, color);
	setPixel2UC(surface, x + 30, y, color);

	//setPixelUC(surface, x, y, 0xFFFF00FF);
}

inline static void setHLine16(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
	//color = 0xFFFFFF00FFFFFF00;

	setPixel2UC(surface, x + 0, y, color);
	setPixel2UC(surface, x + 2, y, color);
	setPixel2UC(surface, x + 4, y, color);
	setPixel2UC(surface, x + 6, y, color);
	setPixel2UC(surface, x + 8, y, color);
	setPixel2UC(surface, x + 10, y, color);
	setPixel2UC(surface, x + 12, y, color);
	setPixel2UC(surface, x + 14, y, color);

	//setPixelUC(surface, x, y, 0xFFFF00FF);
}

inline static void setHLine8(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
	//color = 0xFF00FF00FF00FF00;

	setPixel2UC(surface, x + 0, y, color);
	setPixel2UC(surface, x + 2, y, color);
	setPixel2UC(surface, x + 4, y, color);
	setPixel2UC(surface, x + 6, y, color);

	//setPixelUC(surface, x, y, 0xFFFF00FF);
}
#endif

static void setRect(SDL_Surface* surface, Uint32 x, Uint32 y, Uint32 w, Uint32 h, Uint32 color)
{
	Uint64 color64 = color | (Uint64)color << 32;
	SSE_BEGIN;

	for (Uint32 iy = 0; iy < h; iy++)
	{
		Sint32 align = (4 - ((x + (y + iy) * surface->w) & 0b11)) & 0b11;
		for (Sint32 i = 0; i < align && i < w; i++)
			setPixelUC(surface, x + i, y + iy, color);
		for (Uint32 ix = align; ix < w;)
		{
			Sint32 width = w - ix;
			if (width >= 64)
			{
				#ifdef USE_SSE
				setHLine64(surface, ix + x, iy + y, c128);
				#else
				setHLine64(surface, ix + x, iy + y, color64);
				#endif
				ix += 64;
			}
			else if (width >= 32)
			{
				#ifdef USE_SSE
				setHLine32(surface, ix + x, iy + y, c128);
				#else
				setHLine32(surface, ix + x, iy + y, color64);
				#endif
				ix += 32;
			}
			else if (width >= 16)
			{
				#ifdef USE_SSE
				setHLine16(surface, ix + x, iy + y, c128);
				#else
				setHLine16(surface, ix + x, iy + y, color64);
				#endif
				ix += 16;
			}
			else if (width >= 8)
			{
				#ifdef USE_SSE
				setHLine8(surface, ix + x, iy + y, c128);
				#else
				setHLine8(surface, ix + x, iy + y, color64);
				#endif
				ix += 8;
			}
			else if (width >= 4)
			{
				setPixel2UC(surface, x + 0 + ix, y + iy, color64);
				setPixel2UC(surface, x + 2 + ix, y + iy, color64);
				ix += 4;
			}
			else if (width >= 2)
			{
				setPixel2UC(surface, x + ix, y + iy, color64);
				ix += 2;
			}
			else
			{
				setPixelUC(surface, x + ix, y + iy, color);
				ix++;
			}
		}
	}
}

static void drawRect(SDL_Surface* surface, Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint32 color)
{
	const Sint32 border = 0;
	if (w < 0)
	{
		x += w;
		w = -w;
	}
	if (h < 0)
	{
		y += h;
		h = -h;
	}
	if (x < border)
	{
		w += x - border;
		x = border;
	}
	if (y < border)
	{
		h += y - border;
		y = border;
	}
	if (x >= surface->w - border || y >= surface->h - border || w <= 0 || h <= 0)
		return;
	if (x + w >= surface->w - border)
		w = surface->w - border - x;
	if (y + h >= surface->h - border)
		h = surface->h - border - y;

	setRect(surface, x, y, w, h, color);
}

static void clearScreen(SDL_Surface* surface, Uint32 color)
{
	Sint32 w = surface->w;
	Sint32 h = surface->h;
	Sint32 wh = w * h;

	Uint64 color64 = color | (Uint64)color << 32;
	SSE_BEGIN;

	for (Sint32 i = 0; i < wh;)
	{
		Sint32 width = wh - i;
		if (width >= 64)
		{
			#ifdef USE_SSE
			setHLine64(surface, i, 0, c128);
			#else
			setHLine64(surface, i, 0, color64);
			#endif
			i += 64;
		}
		else if (width >= 32)
		{
			#ifdef USE_SSE
			setHLine32(surface, i, 0, c128);
			#else
			setHLine32(surface, i, 0, color64);
			#endif
			i += 32;
		}
		else if (width >= 16)
		{
			#ifdef USE_SSE
			setHLine16(surface, i, 0, c128);
			#else
			setHLine16(surface, i, 0, color64);
			#endif
			i += 16;
		}
		else if (i >= 8)
		{
			#ifdef USE_SSE
			setHLine8(surface, i, 0, c128);
			#else
			setHLine8(surface, i, 0, color64);
			#endif
			i += 8;
		}
		else if (width >= 4)
		{
			setPixel2UC(surface, i, 0, color64);
			setPixel2UC(surface, i + 2, 0, color64);
			i += 4;
		}
		else if (width >= 2)
		{
			setPixel2UC(surface, i, 0, color64);
			i += 2;
		}
		else
		{
			setPixelUC(surface, i, 0, color);
			i++;
		}
	}
}

static void drawCircle(SDL_Surface* surface, Sint32 x, Sint32 y, Sint32 r, Uint32 color)
{
	if (r < 0)
		r = -r;
	if (r == 0)
		return;

	Sint32 xx = x - r;
	Sint32 yy = y - r;
	Sint32 w = r * 2;
	Sint32 h = r * 2;
	const Sint32 border = 0;
	if (xx < border)
	{
		w += xx - border;
		xx = border;
	}
	if (yy < border)
	{
		h += yy - border;
		yy = border;
	}
	if (xx >= surface->w - border || yy >= surface->h - border || w <= 0 || h <= 0)
		return;
	if (xx + w >= surface->w - border)
		w = surface->w - border - xx;
	if (yy + h >= surface->h - border)
		h = surface->h - border - yy;

	r *= r;

	Uint64 color64 = color | (Uint64)color << 32;
	SSE_BEGIN

	for (Sint32 iy = 0; iy < h; iy++)
	{
		Sint32 yp = yy + iy;
		Sint32 ypow = y - yp;

		// Find end points of circle outline, then rectangle fill
		Sint32 ixl = 0;
		for (; ixl < w; ixl++)
		{
			Sint32 xp = xx + ixl;
			Sint32 xpow = x - xp;
			if (xpow * xpow + ypow * ypow <= r)
			{
				break;
			}
		}
		if (ixl == w)
			continue;

		Sint32 ixr = w - 1;
		for (; ixr >= 0; ixr--)
		{
			Sint32 xp = xx + ixr;
			Sint32 xpow = x - xp;
			if (xpow * xpow + ypow * ypow <= r)
			{
				break;
			}
		}
		if (ixr == -1)
			continue;

		Sint32 align = (4 - ((xx + ixl + yp * surface->w) & 0b11)) & 0b11;
		for (Sint32 i = 0; i < align && ixl + i <= ixr; i++)
			setPixelUC(surface, xx + ixl + i, yp, color);
		for (Sint32 ix = ixl + align; ix <= ixr; )
		{
			Sint32 width = ixr - 1 - ix;
			if (width >= 64)
			{
				#ifdef USE_SSE
				setHLine64(surface, xx + ix, yp, c128);
				#else
				setHLine64(surface, xx + ix, yp, color64);
				#endif
				ix += 64;
			}
			else if (width >= 32)
			{
				#ifdef USE_SSE
				setHLine32(surface, xx + ix, yp, c128);
				#else
				setHLine32(surface, xx + ix, yp, color64);
				#endif
				ix += 32;
			}
			else if (width >= 16)
			{
				#ifdef USE_SSE
				setHLine16(surface, xx + ix, yp, c128);
				#else
				setHLine16(surface, xx + ix, yp, color64);
				#endif
				ix += 16;
			}
			else if (width >= 8)
			{
				#ifdef USE_SSE
				setHLine8(surface, xx + ix, yp, c128);
				#else
				setHLine8(surface, xx + ix, yp, color64);
				#endif
				ix += 8;
			}
			else if (width >= 4)
			{
				setPixel2UC(surface, xx + ix + 0, yp, color64);
				setPixel2UC(surface, xx + ix + 2, yp, color64);
				ix += 4;
			}
			else if (width >= 2)
			{
				setPixel2UC(surface, xx + ix, yp, color64);
				ix += 2;
			}
			else
			{
				setPixelUC(surface, xx + ix, yp, color);
				ix++;
			}
		}
	}
}


#include "bulletinV1_font.h"

static void getTextSize(const char* text, Uint32 size, Uint32* width, Uint32* height)
{
	*width = 0;
	*height = 0;

	if (!text)
		return;

	*height = 1;

	Uint32 x = 0;
	Uint32 y = 1;

	for (Uint32 i = 0; text[i]; i++)
	{
		if (text[i] == '\n')
		{
			if (x > *width)
				*width = x;
			y += 1;
			x = 0;
		}
		else
		{
			x += 1;
			*height = y;
		}
	}
	if (x > *width)
		*width = x;

	if (size)
	{
		*width *= size * font_w;
		*height *= size * font_h;
	}
	else
	{
		*width *= font_w / 2;
		*height *= font_h / 2;
	}
}

static inline bool getArrayBit(Uint32 array[], Uint32 i)
{
	Uint32 index = i >> 5;
	Uint32 shift = 31 - (i & 0b11111);
	return (array[index] >> shift) & 1;
}

static void drawChar(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 size, Uint32 color, char ch)
{
	const int border = 0;

	Sint32 index = (ch - ' ') * (stride / 32);
	if (x >= border && y >= border &&
		x + size * font_w < surface->w - border &&
		y + size * font_h < surface->h - border)
	{
		for (Sint32 fy = 0; fy < font_h; fy++)
			for (Sint32 fx = 0; fx < font_w; fx++)
				if (getArrayBit(&font[index], fx + fy * font_w))
					for (Sint32 ix = 0; ix < size; ix++)
						for (Sint32 iy = 0; iy < size; iy++)
							setPixelUC(surface, x + fx * size + ix, y + fy * size + iy, color);
	}
	else if (x + size * font_w >= border && y + size * font_h >= border &&
		x < surface->w - border && y < surface->h - border)
	{
		for (Sint32 fy = 0; fy < font_h; fy++)
			for (Sint32 fx = 0; fx < font_w; fx++)
				if (getArrayBit(&font[index], fx + fy * font_w))
					for (Sint32 ix = 0; ix < size; ix++)
						for (Sint32 iy = 0; iy < size; iy++)
							setPixel(surface, x + fx * size + ix, y + fy * size + iy, color);
	}
}

// Hacky way of reducing text size, samples top left of 2x2 pixel section
static void drawCharZero(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 color, char ch)
{
	const int border = 0;

	Sint32 index = (ch - ' ') * (stride / 32);
	if (x >= border && y >= border &&
		x + font_w / 2 < surface->w - border &&
		y + font_h / 2 < surface->h - border)
	{
		for (Sint32 fy = 0; fy < font_h; fy += 2)
			for (Sint32 fx = 0; fx < font_w; fx += 2)
				if (getArrayBit(&font[index], fx + fy * font_w))
					setPixelUC(surface, x + fx / 2, y + fy / 2, color);
	}
	else if (x + font_w / 2 >= border && y + font_h / 2 >= border &&
		x < surface->w - border && y < surface->h - border)
	{
		for (Sint32 fy = 0; fy < font_h; fy += 2)
			for (Sint32 fx = 0; fx < font_w; fx += 2)
				if (getArrayBit(&font[index], fx + fy * font_w))
					setPixel(surface, x + fx / 2, y + fy / 2, color);
	}
}

static void drawText(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 size, Uint32 color, const char* text)
{
	Sint32 xx = 0;
	Sint32 yy = 0;
	for (Sint32 i = 0; text[i]; i++)
	{
		if (text[i] == '\n')
		{
			xx = 0;
			yy += (size ? size * font_h : font_h / 2);
		}
		else if (text[i] >= 127 || text[i] < ' '); // unknown
		else
		{
			if (size > 0)
				drawChar(surface, x + xx, y + yy, size, color, text[i]);
			else
				drawCharZero(surface, x + xx, y + yy, color, text[i]); 
			xx += (size ? size * font_w : font_w / 2);
		}
	}
}

static void drawTextF(SDL_Surface* surface, Sint32 x, Sint32 y, Sint32 size, Uint32 color, const char* fmt, ...)
{
	va_list prf0, prf1;
	va_start(prf0, fmt);

	va_copy(prf1, prf0);
	Sint32 len = vsnprintf(NULL, 0, fmt, prf0);
	va_end(prf0);

	if (len <= 100)
	{
		char* smBuf[100];
		vsnprintf(smBuf, 100, fmt, prf1);
		drawText(surface, x, y, size, color, smBuf);
	}
	else
	{
		char* buf = malloc(len);
		if (buf)
		{
			vsnprintf(buf, len, fmt, prf1);
			drawText(surface, x, y, size, color, buf);
			free(buf);
		}
	}

	va_end(prf1);
}

static void getTextSizeF(Uint32 size, Uint32* width, Uint32* height, const char* fmt, ...)
{
	va_list prf0, prf1;
	va_start(prf0, fmt);

	va_copy(prf1, prf0);
	Sint32 len = vsnprintf(NULL, 0, fmt, prf0);
	va_end(prf0);

	if (len <= 100)
	{
		char* smBuf[100];
		vsnprintf(smBuf, 100, fmt, prf1);
		getTextSize(smBuf, size, width, height);
	}
	else
	{
		char* buf = malloc(len);
		if (buf)
		{
			vsnprintf(buf, len, fmt, prf1);
			getTextSize(buf, size, width, height);
			free(buf);
		}
	}

	va_end(prf1);
}