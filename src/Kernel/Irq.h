#pragma once

#include "Util.h"
#include "Isr.h"

namespace Irq
{
	void Init();
	void Install(uint i, Isr::Stub handler);
}