#include "Util.h"

enum ScreenData
{
	WIDTH = 360,
	HEIGHT = 200,
	SCREEN_SIZE = WIDTH * HEIGHT,
};

extern byte pixels[SCREEN_SIZE];
#define DrawPixel(x, y, col) pixels[(uint)((x) + (y) * WIDTH)] = (col)

extern void SwapBuffers();