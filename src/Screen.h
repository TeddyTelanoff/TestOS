#include "Util.h"

enum ScreenData
{
	WIDTH = 320,
	HEIGHT = 200,
	SCREEN_SIZE = WIDTH * HEIGHT,
};

enum class ScreenMode
{
	Text = 0x00,
	Color = 0x13,
};

#define DrawPixel(x, y, col) pixels[(uint)((x) + (y) * WIDTH)] = (col)

namespace Screen
{
	extern byte pixels[SCREEN_SIZE];
	extern void SwapBuffers();
}

using namespace Screen;