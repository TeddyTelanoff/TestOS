#pragma once

#include "Util.h"
#include "System.h"

namespace Font
{
	template<uint base, uint len>
	inline void Num(uint num, char (&buff)[len])
	{
		uint digit;
		for (uint i = len - 1; i; i--)
		{
			digit = num % base;
			buff[i - 1] = digit < 10 ? digit + '0' : digit + 'A';
			num /= base;
		}

		buff[len - 1] = null;
	}

	void DrawChar(char c, uint x, uint y, byte col = 0xF);
	void DrawStr(const char *str, uint x, uint y, byte col = 0xF);
}