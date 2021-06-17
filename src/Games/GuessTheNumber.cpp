#include "Kernel/System.h"
#include "Kernel/Time.h"
#include "Kernel/Keyboard.h"
#include "Kernel/Sound.h"

void Main()
{ while (true); }

void Guess(uint n)
{
	uint actual = System::Random(4);

	if (n == actual)
		Sound::Beep(370, Time::Tps / 2);
	else
		Sound::Beep(44, Time::Tps / 2);
}

void KeyPress(KeyCode keyCode, word mods)
{
	switch (keyCode)
	{
	case Key::A:
	case Key::LeftArrow:
		Guess(0);
		break;
	case Key::D:
	case Key::RightArrow:
		Guess(1);
		break;
	case Key::S:
	case Key::DownArrow:
		Guess(2);
		break;
	case Key::W:
	case Key::UpArrow:
		Guess(3);
		break;
	}
}

void KeyRelease(KeyCode keyCode, word mods)
{}