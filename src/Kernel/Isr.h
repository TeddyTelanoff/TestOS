#pragma once

#include "Util.h"

namespace Isr
{
	enum Data
	{
		Count = 48,
	};

	struct Registers
	{
		uint _, fs, es, ds;
		uint di, si, bp, sp, bx, dx, cx, ax;
		uint intNum, errNum;
		uint ip, cs, fl, userSp, ss;
	};

	using Stub = void (*)(Registers &);

	extern const char *exceptions[32];
	extern Stub stubs[Count];

	extern void Init();
	extern void Install(uint i, Stub handler);

	extern "C"
	{
		extern void _isr0(Registers &);
		extern void _isr1(Registers &);
		extern void _isr2(Registers &);
		extern void _isr3(Registers &);
		extern void _isr4(Registers &);
		extern void _isr5(Registers &);
		extern void _isr6(Registers &);
		extern void _isr7(Registers &);
		extern void _isr8(Registers &);
		extern void _isr9(Registers &);
		extern void _isr10(Registers &);
		extern void _isr11(Registers &);
		extern void _isr12(Registers &);
		extern void _isr13(Registers &);
		extern void _isr14(Registers &);
		extern void _isr15(Registers &);
		extern void _isr16(Registers &);
		extern void _isr17(Registers &);
		extern void _isr18(Registers &);
		extern void _isr19(Registers &);
		extern void _isr20(Registers &);
		extern void _isr21(Registers &);
		extern void _isr22(Registers &);
		extern void _isr23(Registers &);
		extern void _isr24(Registers &);
		extern void _isr25(Registers &);
		extern void _isr26(Registers &);
		extern void _isr27(Registers &);
		extern void _isr28(Registers &);
		extern void _isr29(Registers &);
		extern void _isr30(Registers &);
		extern void _isr31(Registers &);
		extern void _isr32(Registers &);
		extern void _isr33(Registers &);
		extern void _isr34(Registers &);
		extern void _isr35(Registers &);
		extern void _isr36(Registers &);
		extern void _isr37(Registers &);
		extern void _isr38(Registers &);
		extern void _isr39(Registers &);
		extern void _isr40(Registers &);
		extern void _isr41(Registers &);
		extern void _isr42(Registers &);
		extern void _isr43(Registers &);
		extern void _isr44(Registers &);
		extern void _isr45(Registers &);
		extern void _isr46(Registers &);
		extern void _isr47(Registers &);
	}
}