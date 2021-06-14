#include "Util.h"

#define PixelAt(i, c) pixels[i / WIDTH][i % WIDTH] = (c)

namespace Screen
{
	enum ScreenData
	{
		WIDTH = 320,
		HEIGHT = 200,
		SCREEN_SIZE = WIDTH * HEIGHT,
	};
	
	extern void SetPixel(int x, int y, byte col);
	extern void SwapBuffers();
}

using namespace Screen;