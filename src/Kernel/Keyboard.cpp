#include "Keyboard.h"
#include "Key.h"
#include "Irq.h"
#include "Font.h"
#include "Screen.h"

extern void KeyPress(KeyCode key);
extern void KeyRelease(KeyCode key);

namespace
{
	using namespace Keyboard;

	void Handler(Isr::Registers &regs)
	{
		word scancode = InPortB(0x60);

		bool isPress = KEY_IS_PRESS(scancode);
		word keyCode = KEY_SCANCODE(scancode);

		// Set mods
		if (keyCode == Key::LeftShift || keyCode == Key::RightShift)
			mods = BIT_SET(mods, HIBIT(Key::Mod::Shift), isPress);
		else if (keyCode == Key::Alt)
			mods = BIT_SET(mods, HIBIT(Key::Mod::Alt), isPress);
		else if (keyCode == Key::Ctrl )
			mods = BIT_SET(mods, HIBIT(Key::Mod::Ctrl), isPress);
		else if (keyCode == Key::CapsLock)
			mods = BIT_SET(mods, HIBIT(Key::Mod::CapsLock), isPress);
		else if (keyCode == Key::NumLock)
			mods = BIT_SET(mods, HIBIT(Key::Mod::NumLock), isPress);
		else if (keyCode == Key::ScrollLock)
			mods = BIT_SET(mods, HIBIT(Key::Mod::ScrollLock), isPress);

		latest = keyCode;
		if (keyCode < 128)
		{
			keys[keyCode] = isPress;
			if (isPress)
				KeyPress(keyCode);
			else
				KeyRelease(keyCode);
		}
	}
}

word Keyboard::mods;
word Keyboard::latest;
bool Keyboard::keys[128];;

void Keyboard::Init()
{ Irq::Install(1, Handler); }