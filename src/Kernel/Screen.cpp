#include "Screen.h"

namespace
{
	byte *buffer = (byte *)0xA0000;
}

byte Screen::pixels[Screen::Size] = {};

void Screen::Clear(byte col)
{ Set(pixels, col, Size); }

void Screen::SetPixel(int x, int y, byte col)
{
	if (x < 0 || x >= Width ||
		y < 0 || y >= Height)
			return;
	
	pixels[x + y * Width] = col;
}

void Screen::SwapBuffers()
{ Copy(pixels, buffer, Size); }