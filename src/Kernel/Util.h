#pragma once

using byte = unsigned char;
using word = unsigned short;
using uint = unsigned int;
using ulong = unsigned long long;

#ifndef asm
#define asm __asm__ volatile
#endif

namespace
{
	inline void OutPortB(word port, byte dat)
	{ asm("outb %1, %0" : : "dN" (port), "a" (dat)); }

	template<typename T>
	inline void Set(T *obj, byte val, uint count)
	{
		count *= sizeof(T);
		byte *ptr = (byte *)obj;
		
		while (count--)
			*ptr++ = val;
	}

	template<typename T>
	inline void Copy(const T *from, T *to, uint count)
	{
		const T *read = from;
		T *write = to;

		while (count--)
			*write++ = *read++;
	}
}