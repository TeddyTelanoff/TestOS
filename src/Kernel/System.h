#pragma once

#include "Util.h"
#include "Time.h"

#define STRINGIFY(x) _STRINGIFY(x)
#define _STRINGIFY(x) #x
#define ASSERT(expr) if (!(expr)) System::Panic("(" __FILE__ ":" STRINGIFY(__LINE__) ") Assertion Error: " #expr);

namespace System
{
	extern uint randSeed;

	extern uint Hash(uint);
	extern void Log(const char *msg, uint durationInTicks = Time::Tps);
	extern void Panic(const char *err = nullptr);
	extern void ReBoot();

	template<typename T>
	inline T Random()
	{ return (T)Hash(randSeed++); }

	template<>
	bool Random();

	template<>
	float Random();

	template<typename T>
	inline T Random(T max)
	{ return (T)(Hash(randSeed++) % max); }

	template<>
	float Random(float max);
	
	template<typename T>
	inline T Random(T min, T max)
	{ return (T)(Hash(randSeed++) % (max - min) + min); }

	template<>
	float Random(float min, float max);
}