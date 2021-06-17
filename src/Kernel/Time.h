#pragma once

#include "Util.h"

namespace Time
{
	enum Data
	{
		Tps = 420,
	};

	using Event = void (*)();

	extern void Init();
	extern ulong GetTime();
	extern void Schedule(Event, uint delay);
}