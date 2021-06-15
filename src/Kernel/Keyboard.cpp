#include "Keyboard.h"
#include "Key.h"
#include "Irq.h"

namespace
{
	using namespace Keyboard;

	void Handler(Isr::Registers &regs)
	{
		word scancode = InPortB(0x60);
		bool isPress = KEY_IS_PRESS(scancode);
		word keyCode = KEY_SCANCODE(scancode);

		// Set mods
		if (keyCode == Key::LeftAlt || keyCode == Key::RightAlt)
			mods = BIT_SET(mods, HIBIT(Key::Mod::Alt), isPress);
		else if (keyCode == Key::LeftCtrl || keyCode == Key::RightCtrl)
			mods = BIT_SET(mods, HIBIT(Key::Mod::Ctrl), isPress);
		else if (keyCode == Key::LeftShift || keyCode == Key::RightShift)
			mods = BIT_SET(mods, HIBIT(Key::Mod::Shift), isPress);
		else if (keyCode == Key::CapsLock)
			mods = BIT_SET(mods, HIBIT(Key::Mod::CapsLock), isPress);
		else if (keyCode == Key::NumLock)
			mods = BIT_SET(mods, HIBIT(Key::Mod::NumLock), isPress);
		else if (keyCode == Key::ScrollLock)
			mods = BIT_SET(mods, HIBIT(Key::Mod::ScrollLock), isPress);

		keys[keyCode] = isPress;
	}
}

byte Keyboard::keys[Key::Count];
byte Keyboard::chars[Key::Count];

using namespace Key;
Layout Keyboard::LayoutUs = {
	{
		Null, Escape, D1, D2, D3, D4, D5, D6, D7, D8, D9, D0, Minus, Equal, Backspace,
		Tab, Q, W, E, R, T, Y, U, I, O, P, LeftBracket, RightBracket, Backslash,
		CapsLock, A, S, D, F, G, H, J, K, L, Semicolon, Apostrophe, Enter,
		LeftShift, Z, X, C, V, B, N, M, Comma, Period, Slash, RightShift,

	},
};

void Keyboard::Init()
{ Irq::Install(1, Handler); }