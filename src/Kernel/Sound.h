#pragma once

#include "Util.h"

namespace Sound
{
	void Beep();
	void Play(word freq);
	void Mute();
	void Tick();
	bool Enabled();
}