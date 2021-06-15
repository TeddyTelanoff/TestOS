#pragma once

#include "Util.h"
#include "Key.h"

namespace Keyboard
{
	using Layout = byte[2][128];

	extern Layout LayoutUs;

	extern word mods;
	extern byte keys[Key::Count];

	void Init();
}