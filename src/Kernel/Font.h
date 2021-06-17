#pragma once

#include "Util.h"
#include "System.h"

namespace Font
{
	template<uint base = 10, uint len>
	inline void FNum(uint num, char (&buff)[len], bool fillAll = false)
	{
		uint digit;
		for (uint i = len - 1; i; i--)
		{
			digit = num % base;
			buff[i - 1] = digit < 10 ? digit + '0' : digit - 10 + 'A';
			if (!(num /= base))
				break;
		}

		buff[len - 1] = null;
	}

	void DrawChar(char c, uint x, uint y, byte col = 0xF);

	void DrawStr(const char *str, uint x, uint y, byte col = 0xF);
	void DrawStrDoubled(const char *str, uint x, uint y, byte col1 = 0xF, byte col2 = 0x07);

	void DrawStrW(const char *str, uint x, uint y, uint w, byte col = 0xF);
	void DrawStrDoubledW(const char *str, uint x, uint y, uint w, byte col1 = 0xF, byte col2 = 0x07);
}