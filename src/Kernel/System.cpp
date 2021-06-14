#include "System.h"
#include "Screen.h"
#include "Font.h"

void System::Panic(const char *err)
{
	Screen::Clear(0x37);
	Font::DrawStr(err, 5, 5, 0x0C);
	Screen::SwapBuffers();
	while (true);
}