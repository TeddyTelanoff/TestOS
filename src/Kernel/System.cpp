#include "System.h"
#include "Screen.h"

void System::Panic(const char *err)
{
	Screen::Clear(0x37);
	Screen::SwapBuffers();
	while (true);
}