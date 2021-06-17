#pragma once

#include "Util.h"

namespace Screen
{
	enum Data
	{
		Width = 320,
		Height = 200,
		Size = Width * Height,
	};
	
	extern byte pixels[Screen::Size];

	extern void Clear(byte col = 0);
	extern void SetPixel(int x, int y, byte col);
	extern void SwapBuffers();
}