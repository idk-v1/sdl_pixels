#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


#ifdef __cplusplus
#define PIXEL_FN extern "C" 
#else
#define PIXEL_FN
#endif

#ifdef __cplusplus
extern "C" { extern const SDL_PixelFormatDetails* pixFmt; }
#else
extern const SDL_PixelFormatDetails* pixFmt;
#endif

PIXEL_FN inline Uint32 rgb(Uint8 r, Uint8 g, Uint8 b);


PIXEL_FN inline void setPixelUC(SDL_Surface* surface, Uint32 x, Uint32 y, Uint32 color);

PIXEL_FN inline void setPixel2UC(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color);

PIXEL_FN inline void setPixel(SDL_Surface* surface, Uint32 x, Uint32 y, Uint32 color);


#ifdef USE_SSE
#include <immintrin.h>

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
#else
#define SSE_BEGIN
#endif

#ifdef USE_SSE
PIXEL_FN inline static void setHLine64(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	// extreme alignment needed to not crash (16 bytes)
	// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_mm_stream_ps&ig_expand=6562
	// make sure caller passes aligned values
	Uint32* pixels = ((Uint32*)surface->pixels + (x + y * surface->w));
	_mm_stream_ps((float*)(pixels + 0), color);
	_mm_stream_ps((float*)(pixels + 4), color);
	_mm_stream_ps((float*)(pixels + 8), color);
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

PIXEL_FN inline static void setHLine32(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	Uint32* pixels = &(((Uint32*)surface->pixels)[x + y * surface->w]);
	_mm_stream_ps((float*)(pixels + 0), color);
	_mm_stream_ps((float*)(pixels + 4), color);
	_mm_stream_ps((float*)(pixels + 8), color);
	_mm_stream_ps((float*)(pixels + 12), color);
	_mm_stream_ps((float*)(pixels + 16), color);
	_mm_stream_ps((float*)(pixels + 20), color);
	_mm_stream_ps((float*)(pixels + 24), color);
	_mm_stream_ps((float*)(pixels + 28), color);
}

PIXEL_FN inline static void setHLine16(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	Uint32* pixels = &(((Uint32*)surface->pixels)[x + y * surface->w]);
	_mm_stream_ps((float*)(pixels + 0), color);
	_mm_stream_ps((float*)(pixels + 4), color);
	_mm_stream_ps((float*)(pixels + 8), color);
	_mm_stream_ps((float*)(pixels + 12), color);
}

PIXEL_FN inline static void setHLine8(SDL_Surface* surface, Uint32 x, Uint32 y, __m128 color)
{
	Uint32* pixels = &(((Uint32*)surface->pixels)[x + y * surface->w]);
	_mm_stream_ps((float*)(pixels + 0), color);
	_mm_stream_ps((float*)(pixels + 4), color);
}
#else
PIXEL_FN inline static void setHLine64(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
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
}

PIXEL_FN inline static void setHLine32(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
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
}

PIXEL_FN inline static void setHLine16(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
	setPixel2UC(surface, x + 0, y, color);
	setPixel2UC(surface, x + 2, y, color);
	setPixel2UC(surface, x + 4, y, color);
	setPixel2UC(surface, x + 6, y, color);
	setPixel2UC(surface, x + 8, y, color);
	setPixel2UC(surface, x + 10, y, color);
	setPixel2UC(surface, x + 12, y, color);
	setPixel2UC(surface, x + 14, y, color);
}

PIXEL_FN inline static void setHLine8(SDL_Surface* surface, Uint32 x, Uint32 y, Uint64 color)
{
	setPixel2UC(surface, x + 0, y, color);
	setPixel2UC(surface, x + 2, y, color);
	setPixel2UC(surface, x + 4, y, color);
	setPixel2UC(surface, x + 6, y, color);
}
#endif

PIXEL_FN inline static void setLine(SDL_Surface* surface, Uint32 x, Uint32 y, Uint32 w, Uint32 color)
{
	Uint64 color64 = color | (Uint64)color << 32;
#ifdef USE_SSE
	SSE_BEGIN;
#endif

	Sint32 align = (4 - ((x + y * surface->w) & 0b11)) & 0b11;
	for (Sint32 i = 0; i < align && i < w; i++)
		setPixelUC(surface, x + i, y, color);

	for (Uint32 ix = align; ix < w;)
	{
		Sint32 width = w - ix;
		if (width >= 64)
		{
#ifdef USE_SSE
			setHLine64(surface, ix + x, y, c128);
#else
			setHLine64(surface, ix + x, y, color64);
#endif
			ix += 64;
		}
		else if (width >= 32)
		{
#ifdef USE_SSE
			setHLine32(surface, ix + x, y, c128);
#else
			setHLine32(surface, ix + x, y, color64);
#endif
			ix += 32;
		}
		else if (width >= 16)
		{
#ifdef USE_SSE
			setHLine16(surface, ix + x, y, c128);
#else
			setHLine16(surface, ix + x, y, color64);
#endif
			ix += 16;
		}
		else if (width >= 8)
		{
#ifdef USE_SSE
			setHLine8(surface, ix + x, y, c128);
#else
			setHLine8(surface, ix + x, y, color64);
#endif
			ix += 8;
		}
		else if (width >= 4)
		{
			setPixel2UC(surface, x + 0 + ix, y, color64);
			setPixel2UC(surface, x + 2 + ix, y, color64);
			ix += 4;
		}
		else if (width >= 2)
		{
			setPixel2UC(surface, x + ix, y, color64);
			ix += 2;
		}
		else
		{
			setPixelUC(surface, x + ix, y, color);
			ix++;
		}
	}
}


PIXEL_FN void setRect(SDL_Surface* surface, Uint32 x, Uint32 y,
	Uint32 w, Uint32 h, Uint32 color);

PIXEL_FN void clearScreen(SDL_Surface* surface, Uint32 color);


PIXEL_FN PIXEL_FN void drawRect(SDL_Surface* surface, Sint32 x, Sint32 y,
	Sint32 w, Sint32 h, Uint32 color);

PIXEL_FN void drawRectA(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Sint32 w, Sint32 h, Uint32 color);

PIXEL_FN void drawRectOut(SDL_Surface* surface, Sint32 x, Sint32 y,
	Sint32 w, Sint32 h, Uint32 size, Uint32 color);

PIXEL_FN void drawRectOutA(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Sint32 w, Sint32 h, Uint32 size, Uint32 color);


PIXEL_FN void drawCircle(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 r, Uint32 color);

PIXEL_FN void drawCircleA(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Uint32 r, Uint32 color);


extern int letterSpacing;
extern int lineSpacing;

PIXEL_FN void getTextSize(const char* text, Uint32 size, Uint32* width, Uint32* height);

PIXEL_FN void getTextSizeF(Uint32 size, Uint32* width, Uint32* height, const char* fmt, ...);

PIXEL_FN void drawChar(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 size,
	Uint32 color, char ch);

PIXEL_FN void drawCharA(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Uint32 size, Uint32 color, char ch);

PIXEL_FN void drawText(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 size,
	Uint32 color, const char* text);

PIXEL_FN void drawTextA(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Uint32 size, Uint32 color, const char* text);

PIXEL_FN void drawTextF(SDL_Surface* surface, Sint32 x, Sint32 y, Sint32 size,
	Uint32 color, const char* fmt, ...);

PIXEL_FN void drawTextFA(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Sint32 size, Uint32 color, const char* fmt, ...);

PIXEL_FN void drawTextFn(SDL_Surface* surface, Sint32 x, Sint32 y, Uint32 size, Uint32 color,
	void(before)(SDL_Surface*, Sint32, Sint32, Sint32, Sint32, char, void*), 
	void* data, const char* text);

PIXEL_FN void drawTextAFn(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Uint32 size, Uint32 color,
	void(before)(SDL_Surface*, Sint32, Sint32, Sint32, Sint32, char, void*),
	void* data, const char* text);

PIXEL_FN void drawTextFFn(SDL_Surface* surface, Sint32 x, Sint32 y, Sint32 size, Uint32 color,
	void(before)(SDL_Surface*, Sint32, Sint32, Sint32, Sint32, char, void*),
	void* data, const char* fmt, ...);

PIXEL_FN void drawTextFAFn(SDL_Surface* surface, Sint32 x, Sint32 y,
	float alignX, float alignY, Sint32 size, Uint32 color,
	void(before)(SDL_Surface*, Sint32, Sint32, Sint32, Sint32, char, void*),
	void* data, const char* fmt, ...);


#ifdef __cplusplus
struct Bitmap
{
	Uint32 width, height;
	Uint32* pixels;
};
#else
typedef struct Bitmap
{
	Uint32 width, height;
	Uint32* pixels;
} Bitmap;
#endif

PIXEL_FN Bitmap loadImage(const char* filename);

PIXEL_FN void freeImage(Bitmap* image);

PIXEL_FN void drawImage(SDL_Surface* surface, Bitmap* image, Sint32 destX, Sint32 destY,
	Sint32 srcX, Sint32 srcY, Sint32 width, Sint32 height);

PIXEL_FN void drawImageA(SDL_Surface* surface, Bitmap* image, Sint32 destX, Sint32 destY,
	Sint32 srcX, Sint32 srcY, Sint32 width, Sint32 height, float alignX, float alignY);