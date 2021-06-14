#pragma once

#include "Util.h"

namespace Time
{
	enum Data
	{
		Tps = 60,
	};

	extern void Init();
	extern ulong GetTime();
}