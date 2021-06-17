#pragma once

#include "Util.h"
#include "Time.h"

namespace Sound
{
	void Beep(word freq = 555, uint duration = Time::Tps);
	void Play(word freq);
	void PlayRaw(word note);
	void Stop();

	void ToggleMute();
	bool IsMuted();
	void SetMute(bool mute);

	bool Enabled();
}