#include "Time.h"
#include "Irq.h"
#include "System.h"

namespace
{
	ulong freq, div, ticks;
	struct
	{
		Time::Event event;
		ulong when;
	} events[16] = {};

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

	void Handler(Isr::Registers &regs)
	{
		ticks++;
		for (auto &e : events)
			if (e.when && ticks >= e.when)
			{
				e.event();
				e.when = 0;
			}
	}
}

void Time::Init()
{
	freq = Tps;
	div = PIT::Hertz / freq;
	ticks = 0;

	SetTimer(Tps);
	Irq::Install(0, Handler);
}

ulong Time::GetTime()
{ return ticks; }

void Time::Schedule(Event ev, uint delay)
{
	for (auto &e : events)
		if (e.when == 0)
		{
			e.event = ev;
			e.when = ticks + delay;
			return;
		}

	System::Panic("Ran out of empty events!");
}