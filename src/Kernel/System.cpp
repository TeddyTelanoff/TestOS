#include "System.h"
#include "Screen.h"
#include "Font.h"

uint System::randSeed;

uint System::Hash(uint n)
{
	n ^= 2747636419;
	n *= 2654435769;

	n ^= n >> 16;
	n *= 2654435769;

	n ^= n >> 16;
	n *= 2654435769;
	return n;
}

void System::ReBoot()
{
	// Unimplemented...
}

void System::Log(const char *msg, uint duration)
{
	Screen::Clear(0x37);
	Font::DrawStr(msg, 4, 4, 0x0F);
	Screen::SwapBuffers();

	uint now = Time::GetTime();
	while (Time::GetTime() - now <= duration);
}

void System::Panic(const char *err)
{
	Screen::Clear(0x37);
	if (err == null)
		Font::DrawStr("System Panic Called!", 4, 4, 0x0F);
	else
		Font::DrawStr(err, 4, 4, 0x0F);
	Screen::SwapBuffers();
	while (true);
}

#define RAND(ty) template<> ty System::Random() { return (ty)Hash(randSeed++); }
#define RAND_MAX(ty) template<> ty System::Random(ty max) { return (ty)Hash(randSeed++) % max; }
#define RAND_RANGE(ty) template<> ty System::Random(ty min, ty max) { return min + ((ty)Hash(randSeed++) % (max - min)); }

template<>
float System::Random()
{ return (float)Hash(randSeed++) / (float)0xFFFFFFFFFFFFFFFF; }

template<>
bool System::Random()
{ return Hash(randSeed++) & 1; }

template<>
float System::Random(float max)
{ return ((float)Hash(randSeed++) * max / (float)0xFFFFFFFFFFFFFFFF); }

template<>
float System::Random(float min, float max)
{ return ((float)Hash(randSeed++) / (float)0xFFFFFFFFFFFFFFFF) * (max - min) + min; }