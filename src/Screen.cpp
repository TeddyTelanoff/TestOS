#include "Screen.h"

static byte *buffer = (byte *)0xA0000;
byte Screen::pixels[SCREEN_SIZE] = {};

void Screen::SwapBuffers()
{
	Copy(pixels, buffer, SCREEN_SIZE);
}