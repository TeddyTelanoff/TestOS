#include "Isr.h"
using namespace Isr;

#include "Idt.h"

void (*Isr::stubs[Count])(Registers &) = {
	_isr0,
	_isr1,
	_isr2,
	_isr3,
	_isr4,
	_isr5,
	_isr6,
	_isr7,
	_isr8,
	_isr9,
	_isr10,
	_isr11,
	_isr12,
	_isr13,
	_isr14,
	_isr15,
	_isr16,
	_isr17,
	_isr18,
	_isr19,
	_isr20,
	_isr21,
	_isr22,
	_isr23,
	_isr24,
	_isr25,
	_isr26,
	_isr27,
	_isr28,
	_isr29,
	_isr30,
	_isr31,
	_isr32,
	_isr33,
	_isr34,
	_isr35,
	_isr36,
	_isr37,
	_isr38,
	_isr39,
	_isr40,
	_isr41,
	_isr42,
	_isr43,
	_isr44,
	_isr45,
	_isr46,
	_isr47,
};

namespace
{
	struct
	{
		uint index;
		Stub stub;
	} isrs[Count];

	Stub handlers[Count] = {};

	void ExceptionHandler(Registers &reg)
	{
		// TODO: Print Error
	}
}

void Isr::Init()
{
	for (uint i = 0; i < Count; i++)
	{
		isrs[i].index = i;
		isrs[i].stub = stubs[i];
		Idt::Set(i, stubs[i], 0x08, 0x8E);
	}

	for (uint i = 0; i < 32; i++)
		Isr::Install(i, ExceptionHandler);
}

void Isr::Install(uint i, Stub handler)
{ handlers[i] = handler; }

// Called from Assembly
extern "C" void IsrHandler(Registers &regs)
{
	if (handlers[regs.intNum])
		handlers[regs.intNum](regs);
}