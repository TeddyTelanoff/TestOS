#include "Screen.h"

static byte *buffer = (byte *)0xA0000;
static byte pixels[HEIGHT][WIDTH] = {};

void Screen::SetPixel(int x, int y, byte col)
{
	if (x < 0 || x >= WIDTH ||
		y < 0 || y >= HEIGHT)
			return;
	
	pixels[y][x] = col;
}

void Screen::SwapBuffers()
{
	Copy((byte *)pixels, buffer, SCREEN_SIZE);
}