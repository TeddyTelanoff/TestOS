#include "Sound.h"

namespace
{
	uint wait;
	bool playing, mute;
}

void Sound::Play(word freq)
{
	if (mute)
		return;

	word div = 1193180 / freq;
	OutPortB(0x43, 0xB6);
	OutPortB(0x42, div & 0xFF);
	OutPortB(0x42, div >> 8);

	if (!playing)
	{
		OutPortB(0x61, InPortB(0x61) | 3);
		playing = true;
	}
}

void Sound::PlayRaw(word note)
{
	if (mute)
		return;
		
	OutPortB(0x43, 0xB6);
	OutPortB(0x42, note & 0xFF);
	OutPortB(0x42, note >> 8);


	if (!playing)
	{
		OutPortB(0x61, InPortB(0x61) | 3);
		playing = true;
	}
}

void Sound::Stop()
{
	playing = false;
	OutPortB(0x61, InPortB(0x61) & 0xFC);
}

void Sound::Beep(word freq, uint duration)
{
	Play(freq);
	Time::Schedule(Stop, duration);
}


void Sound::ToggleMute()
{ mute = !mute; }

void Sound::SetMute(bool mute)
{ ::mute = mute; }