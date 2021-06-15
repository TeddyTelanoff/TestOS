#pragma once

#include "Util.h"
#include "System.h"

namespace Font
{
	template<uint len>
	inline void Decimal(uint num, char (&buff)[len])
	{
		byte digit;
		uint i = 0;

		do
		{
			digit = num % 10;
			buff[i++] = digit + '0';
		} while (num /= 10);
		
		if (i >= len)
			System::Panic("Itioa: Buffer too small");
		buff[i--] = null;

		for (uint j = 0; j < i; j++, i--)
		{
			digit = buff[j];
			buff[j] = buff[i];
			buff[i] = digit;
		}
	}

	template<uint len>
	inline void Hex(uint num, char (&buff)[len])
	{
		byte digit;
		uint i = 0;

		do
		{
			digit = num % 0x10;
			buff[i++] = digit < 10 ? digit + '0' : digit - 10 + 'A';
		} while (num /= 0x10);
		
		if (i >= len)
			System::Panic("Itioa: Buffer too small");
		buff[i--] = null;

		for (uint j = 0; j < i; j++, i--)
		{
			digit = buff[j];
			buff[j] = buff[i];
			buff[i] = digit;
		}
	}

	void DrawChar(char c, uint x, uint y, byte col = 0xF);
	void DrawStr(const char *str, uint x, uint y, byte col = 0xF);
}