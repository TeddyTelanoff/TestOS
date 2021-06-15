#include "Time.h"
#include "Idt.h"
#include "Isr.h"
#include "Irq.h"

#include "Keyboard.h"

extern void Main();

extern "C" void Init()
{
	Idt::Init();
	Isr::Init();
	Irq::Init();
	Time::Init();

	Keyboard::Init();

	Main();
}