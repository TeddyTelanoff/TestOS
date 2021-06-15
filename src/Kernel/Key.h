#pragma once

#include "Util.h"

#define KEY_RELEASE 0x80

#define KEY_IS_PRESS(s) (!((s) & KEY_RELEASE))
#define KEY_IS_RELEASE(s) (!!((s) & KEY_RELEASE))
#define KEY_SCANCODE(s) ((s) & 0x7F)
#define KEY_MOD(s, m) (!!((s) & (m)))

using KeyCode = word;
using KeyMod = word;
namespace Key
{
	// Using Standard US Layout
	enum Keys: KeyCode
	{
		Null,

		Ctrl = 0x1D,
		Alt = 0x38,
		LeftShift = 0x2A,
		RightShift = 0x36,
		CapsLock = 0x3A,
		ScrollLock = 0x46,
		NumLock = 0x45,

		Count,
	};

	namespace Mod
	{
		enum Mods: KeyMod
		{
			Alt = 0x200,
			Ctrl = 0x400,
			Shift = 0x800,
			CapsLock = 0x1000,
			NumLock = 0x2000,
			ScrollLock = 0x4000,
		};
	}
}

#include "Keyboard.h"