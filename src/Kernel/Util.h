#pragma once

using byte = unsigned char;
using word = unsigned short;
using uint = unsigned int;
using ulong = unsigned long long;

#ifndef asm
#define asm __asm__ volatile
#endif

#define CLI() asm ("cli")
#define STI() asm ("sti")

#define PACKED __attribute__((packed))

#define null 0

// Returns the highest set bit of x
// i.e. if x == 0xF, HIBIT(x) == 3 (4th index)
// WARNING: currently only works for up to 32-bit types
#define HIBIT(_x) (31 - __builtin_clz((_x)))

// Returns the lowest set bit of x
#define LOBIT(_x)\
    __extension__({ __typeof__(_x) __x = (_x); HIBIT(__x & -__x); })

// Returns v with n-th bit = x
#define BIT_SET(v, n, x) __extension__( {\
        __typeof__(v) _v = (v); \
        (_v ^ ((-(x) ^ _v) & (1 << (n)))); \
        })

namespace
{
	template<typename T>
	bool BitAt(T n, uint i)
	{ return (n >> (sizeof(T) * 8 - i - 1)) & 1; }

	inline byte InPortB(word port)
	{
		byte r;
		asm("inb %1, %0" : "=a" (r) : "dN" (port));
		return r;
	}

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

	template<typename T>
	inline void Move(const T *from, T *to, uint count)
	{
		if (to < from)
		{
			Copy(from, to, count);
			return;
		}

		for (uint i = count; i; i--)
			to[i - 1] = from[i - 1];
	}
	
	template<uint len>
	inline uint StrLen(char (&str)[len])
	{ return len - 1; }

	inline uint StrLen(const char *str)
	{
		uint len = 0;
		while (*str++)
			len++;
		return len;
	}
}