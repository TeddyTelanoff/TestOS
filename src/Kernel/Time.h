#pragma once

#include "Util.h"

namespace Time
{
	enum Data
	{
		Tps = 420,
	};

	extern void Init();
	extern ulong GetTime();
}