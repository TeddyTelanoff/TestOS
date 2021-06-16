#include "Sound.h"
#include "Time.h"

namespace
{
	uint wait;
}

void Sound::Play(word freq)
{
	word div, tmp;

	div = 1193180 / freq;
	OutPortB(0x43, 0xB6);
	OutPortB(0x42, div);
	OutPortB(0x42, div >> 8);

	tmp = InPortB(0x61);
	if (tmp != (tmp | 3))
		OutPortB(0x61, tmp | 3);
}

void Sound::Mute()
{ OutPortB(0x61, InPortB(0x61) & 0xFC); }

void Sound::Beep()
{
	Play(1000);
	wait = Time::GetTime() + Time::Tps;
}