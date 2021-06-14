#include "Screen.h"

struct Box
{ float x, y, w, h; };

void DrawBox(const Box &box)
{
	for (int y = box.y; y < box.y + box.h; y++)
		for (int x = box.x; x < box.x + box.w; x++)
			DrawPixel(x, y, 0x2F);
}

extern "C" void Main()
{
	DrawBox({ 50, 50, 50, 50 });
	SwapBuffers();

	while (true);
}