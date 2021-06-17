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

		A = 0x1E,
		W = 0x11,
		E = 0x12,
		D = 0x20,
		S = 0x1F,

		R = 0x13,
		M = 0x32,

		LeftArrow = 0x4B,
		UpArrow = 0x48,
		RightArrow = 0x4D,
		DownArrow = 0x50,

		Enter = 0x1C,

		Ctrl = 0x1D,
		Alt = 0x38,
		LeftShift = 0x2A,
		RightShift = 0x36,
		CapsLock = 0x3A,
		ScrollLock = 0x46,
		NumLock = 0x45,
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