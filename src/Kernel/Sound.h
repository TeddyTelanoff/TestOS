#pragma once

#include "Util.h"

namespace Sound
{
	void Beep();
	void Play(uint freq);
	void Stop();
	void Tick();
	bool Enabled();
}