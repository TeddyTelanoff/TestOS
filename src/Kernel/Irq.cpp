#include "Irq.h"

#include "Idt.h"
#include "Isr.h"

namespace
{
	namespace PIC
	{
		enum
		{
			A = 0x20,
			AData,
			AOffset = 0x20,

			B = 0xA0,
			BData,
			BOffset = 0x28,

			EOI = 0x20,
			Mode8086 = 0x01,
		};
	}

	namespace ICW1
	{
		enum
		{
			ICW4 = 0x01,
			Init = 0x10,
		};
	}

	Isr::Stub handlers[32] = {};

	void Stub(Isr::Registers &regs)
	{
		if (regs.intNum <= 47 && regs.intNum >= 32)
		{
			if (handlers[regs.intNum - 32])
				handlers[regs.intNum - 32](regs);
		}

		// Send End Of Interrupt (EOI)
		if (regs.intNum >= 0x40)
			OutPortB(PIC::B, PIC::EOI);
		OutPortB(PIC::A, PIC::EOI);
	}

	void ReMap()
	{
		byte maska = InPortB(PIC::AData), maskb = InPortB(PIC::BData);
		OutPortB(PIC::A, ICW1::Init | ICW1::ICW4);
		OutPortB(PIC::B, ICW1::Init | ICW1::ICW4);

		OutPortB(PIC::AData, PIC::AOffset);
		OutPortB(PIC::BData, PIC::BOffset);

		OutPortB(PIC::AData, 4); // PIC2 at IRQ2
		OutPortB(PIC::BData, 2); // Cascade identitiy

		OutPortB(PIC::AData, PIC::Mode8086);
		OutPortB(PIC::AData, PIC::Mode8086);

		OutPortB(PIC::AData, maska);
		OutPortB(PIC::BData, maskb);
	}

	void SetMask(uint i)
	{
		word port = i < 8 ? PIC::AData : PIC::BData;
		byte val = InPortB(port) | (1 << i);
		OutPortB(port, val);
	}

	void ClearMask(uint i)
	{
		word port = i < 8 ? PIC::AData : PIC::BData;
		byte val = InPortB(port) & ~(1 << i);
		OutPortB(port, val);
	}
}

void Irq::Init()
{
	ReMap();
	for (uint i = 0; i < 16; i++)
		Isr::Install(i + 32, Stub);
}

void Irq::Install(uint i, Isr::Stub handler)
{
	CLI();
	handlers[i] = handler;
	ClearMask(i);
	STI(); // <-- This is giving me problemos
}