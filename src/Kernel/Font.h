#pragma once

#include "Util.h"

namespace Font
{
	void DrawChar(char c, uint x, uint y, byte col);
	void DrawStr(const char *str, uint x, uint y, byte col);
}