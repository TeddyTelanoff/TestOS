#pragma once

#include "Util.h"

namespace System
{
	extern ulong randSeed;

	extern ulong Hash(ulong);
	extern void Panic(const char *err = nullptr);

	template<typename T = uint>
	extern T Random();

	template<typename T = uint>
	extern T Random(T max);
	
	template<typename T = uint>
	extern T Random(T min, T max);
}