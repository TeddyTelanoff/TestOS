#include "Idt.h"

namespace
{
	struct Entry
	{
		word offsetLow;
		word selector;
		byte _;
		byte type;
		word offsetHigh;
	} PACKED;

	struct Pointer
	{
		word limit;
		void *base;
	} PACKED;

	Entry entries[256];
	Pointer ptr;
}

// Assembly fn
extern "C" void IdtLoad(Pointer &);

void Idt::Init()
{
	ptr.limit = sizeof(entries) - 1;
	ptr.base = entries;
	::Set((byte *)entries, 0, sizeof(Entry) * 256);
	IdtLoad(ptr);
}

void Idt::Set(byte i, Isr::Stub handler, word selector, byte flags)
{
	word low = (uint)handler, high = (uint)handler >> 16;

	entries[i] = Entry {
		low, // offsetLow
		selector,
		0, // unused
		(byte)(flags | 0x60), // type
		high, // offsetHigh
	};
}