#pragma once

#include "Util.h"

#define PixelAt(i, c) pixels[i / WIDTH][i % WIDTH] = (c)

namespace Screen
{
	enum Data
	{
		Width = 320,
		Height = 200,
		ScreenSize = Width * Height,
	};
	
	extern void Clear(byte col = 0);
	extern void SetPixel(int x, int y, byte col);
	extern void SwapBuffers();
}