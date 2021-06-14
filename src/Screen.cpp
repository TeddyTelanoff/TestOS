#include "Screen.h"

static byte *buffer = (byte *)0xA0000;
byte pixels[SCREEN_SIZE] = {};

void SwapBuffers()
{
	Copy(pixels, buffer, SCREEN_SIZE);
}