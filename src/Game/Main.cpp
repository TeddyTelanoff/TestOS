#include "Kernel/Screen.h"
#include "Kernel/System.h"
#include "Kernel/Time.h"
#include "Kernel/Keyboard.h"
#include "Kernel/Font.h"
#include "Kernel/Screen.h"

namespace Board
{
	enum Data
	{
		Scale = 12,
		Width = Screen::Width / Scale,
		Height = Screen::Height / Scale,
	};
}

struct Block
{
	enum Data
	{
		Size = 4,
		Scale = Board::Scale,
	};

	using Type = byte;
	enum Types: Type
	{
		I,
		L,
		J,
		O,
		S,
		T,
		Z,

		Count,
	};

	static const constexpr byte Colors[Types::Count][2] = {
		0x4F, 0x37,
		0x09, 0x01,
		0x2A, 0x06,
		0x0E, 0x74,
		0x2F, 0x02,
		0x0D, 0x05,
		0x28, 0x04,
	};

	static const constexpr word Tetriminos[7][4] = {
		{
			0b0000111100000000,
			0b0010001000100010,
			0b0000000011110000,
			0b0100010001000100,
		},
		{
			0b0000010001110000,
			0b0000001100100010,
			0b0000000001110001,
			0b0000001000100110,
		},
		{
			0b0000001011100000,
			0b0000010001000110,
			0b0000000011101000,
			0b0000110001000100,
		},
		{
			0b0000011001100000,
			0b0000011001100000,
			0b0000011001100000,
			0b0000011001100000,
		},
		{
			0b0000011011000000,
			0b0000010001100010,
			0b0000000001101100,
			0b0000100011000100,
		},
		{
			0b0000010011100000,
			0b0000010001100100,
			0b0000000011100100,
			0b0000010011000100,
		},
		{
			0b0000011000110000,
			0b0000000100110010,
			0b0000000001100011,
			0b0000001001100100,
		},
	};

	bool alive;
	int x, y, rot;
	Type type;

	void Draw() const
	{
		for (uint py = 0; py < Size * Scale; py++)
			for (uint px = 0; px < Size * Scale; px++)
			{
				uint tx = px / Scale, ty = py / Scale;
				if (BitAt(Tetriminos[type][rot], tx + ty * Size))
				{
					if (((px + 1) % Scale <= 1) || ((py + 1) % Scale <= 1))
						Screen::SetPixel(x * Scale + px, y * Scale + py, Colors[type][1]);
					else
						Screen::SetPixel(x * Scale + px, y * Scale + py, Colors[type][0]);
				}
			}
	}
};

#define NUM_BLOCKS 64
Block *current;
Block blocks[NUM_BLOCKS] = {};
static char typeBuff[2];
static char rotBuff[2];

void Main()
{
	ulong pFrame = 0;
	while (true)
	{
		ulong now = Time::GetTime();
		if (now - pFrame > Time::Tps)
		{
			pFrame = now;
			if (current)
				current->y++;
			else
			{
				// TODO: Optimize
				for (uint i = 0; i < NUM_BLOCKS; i++)
					if (!blocks[i].alive)
					{
						blocks[i] = { true, Board::Width / 2 - 2, -4, System::Random<uint>(Block::Count), };
						current = &blocks[i];
						break;
					}
			}
		}

		Screen::Clear(0x13);
		for (uint y = 0; y < Board::Height; y++)
			for (uint x = 0; x < Board::Width; x++)
				Screen::SetPixel(x * Board::Scale, y * Board::Scale, 0x08);

		for (const auto &block : blocks)
			if (block.alive)
				block.Draw();
		Font::DrawStr(typeBuff, 5, 5);
		Font::DrawStr(rotBuff, 5, 15);
		Screen::SwapBuffers();
	}
}

void KeyPress(KeyCode keyCode, word mods)
{
	if (current == null)
		return;

	switch (keyCode)
	{
	case Key::LeftArrow:
		current->x--;
		break;
	case Key::RightArrow:
		current->x++;
		break;
	case Key::R:
		if (Keyboard::mods & Key::Mod::Shift)
		{
			current->rot--;
			if (current->rot > 4)
				current->rot = 3;
		}
		else
			current->rot = (current->rot + 1) % 4;
		break;
	}}

void KeyRelease(KeyCode keyCode, word mods)
{}