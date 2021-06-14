#include "Screen.h"

namespace
{
	byte *buffer = (byte *)0xA0000;
	byte pixels[Screen::Height][Screen::Width] = {};
}

void Screen::Clear(byte col)
{ Set((byte *)pixels, col, ScreenSize); }

void Screen::SetPixel(int x, int y, byte col)
{
	if (x < 0 || x >= Width ||
		y < 0 || y >= Height)
			return;
	
	pixels[y][x] = col;
}

void Screen::SwapBuffers()
{
	Copy((byte *)pixels, buffer, ScreenSize);
}