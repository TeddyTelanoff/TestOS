#include "Sound.h"
#include "Time.h"

namespace
{
	uint wait;
}

void Sound::Play(uint freq)
{
	uint div = 1193180 / freq;
	OutPortB(0x43, 0xB6);
	OutPortB(0x42, div & 0xFF);
	OutPortB(0x42, div >> 8);

	OutPortB(0x61, InPortB(0x61) | 3);
}

void Sound::Stop()
{ OutPortB(0x61, InPortB(0x61) & 0xFC); }

void Sound::Beep()
{
	Play(554);
	wait = Time::GetTime() + Time::Tps;
}

void Sound::Tick()
{
	if (Time::GetTime() >= wait)
		Stop();
}