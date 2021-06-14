#pragma once

#include "Util.h"
#include "Isr.h"

namespace Idt
{
	void Init();
	void Set(byte index, Isr::Stub handler, word selector, byte flags);
}