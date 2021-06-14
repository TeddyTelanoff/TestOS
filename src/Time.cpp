#include "Time.h"

namespace
{
	ulong freq, div, ticks;

	namespace PIT
	{
		enum
		{
			A = 0x40,
			B,
			C,
			Control,

			Mask = 0xFF,
			Set = 0x36,

			Hertz = 1193181,
		};
	}

	void SetTimer(int hz)
	{
		OutPortB(PIT::Control, PIT::Set);

		word d = 1193131.666 / hz;
		OutPortB(PIT::A, d & PIT::Mask);
		OutPortB(PIT::A, (d >> 8) & PIT::Mask);
	}
}

void Time::Init()
{
	freq = PIT::Hertz / (PIT::Hertz / Tps);
	div = PIT::Hertz / freq;
	ticks = 0;

	SetTimer(Tps);
}

ulong Time::GetTime()
{ return ticks; }