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
		Width = 10,
		Height = 20,
		Scale = Screen::Height / Height,
		Size = Width * Height,
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
		None,
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

	bool DoesFit(int x, int y, int rot) const;
	void Place();

	void Draw() const;
};

#define NUM_BLOCKS 64
Block *current;
Block blocks[NUM_BLOCKS] = {};
Block::Type board[Board::Width][Board::Height];

static uint startX = Screen::Width / 2 - Board::Width * Board::Scale / 2, endX = Screen::Width / 2 + Board::Width * Board::Scale / 2;
static uint startY = 0, endY = Board::Height * Board::Scale;

bool Block::DoesFit(int x, int y, int rot) const
{
	for (int ty = 0; ty < Size; ty++)
		for (int tx = 0; tx < Size; tx++)
			if (BitAt(Tetriminos[type][rot], tx + ty * Size))
			{
				if (x + tx < 0 || x + tx >= Board::Width)
					return false;
				if (y + ty >= Board::Height)
					return false;
				if (board[x + tx][y + ty] != Block::None)
					return false;
			}
	
	return true;
}

void Block::Place()
{
	current = null;

	for (int ty = 0; ty < Size; ty++)
	{
		for (int tx = 0; tx < Size; tx++)
			if (BitAt(Tetriminos[type][rot], tx + ty * Size))
				board[x + tx][y + ty] = type;
		
		bool rowComplete = true;
		for (uint tx = 0; tx < Board::Width; tx++)
			if (board[tx][y + ty] == Block::None)
			{
				rowComplete = false;
				break;
			}
		
		if (rowComplete)
		{
			for (uint tx = 0; tx < Board::Width; tx++)
			{
				board[tx][y + ty] = Block::None;

				for (uint uy = Board::Height; uy > 1; uy--)
				{
					board[tx][uy - 1] = board[tx][uy - 2];
				}

				board[tx][0] = Block::None;
			}
		}
	}
}
void Block::Draw() const
{
	for (uint py = 0; py < Size * Scale; py++)
		for (uint px = 0; px < Size * Scale; px++)
		{
			uint tx = px / Scale, ty = py / Scale;
			if (BitAt(Tetriminos[type][rot], tx + ty * Size))
			{
				if (((px + 1) % Scale <= 1) || ((py + 1) % Scale <= 1))
					Screen::SetPixel(x * Scale + px + startX, y * Scale + py + startY, Colors[type][1]);
				else
					Screen::SetPixel(x * Scale + px + startX, y * Scale + py + startY, Colors[type][0]);
			}
		}
}

void Draw()
{
	for (uint py = startY; py < endY; py++)
		for (uint px = startX; px < endX; px++)
		{
			uint tx = (px - startX) / Block::Scale, ty = (py - startY) / Block::Scale;
			Block::Type type = board[tx][ty];
			if (type == Block::None)
			{
				if (((px + 1) % Block::Scale <= 1) || ((py + 1) % Block::Scale <= 1))
					Screen::SetPixel(px, py, 0x08);
				continue;
			}

			if (((px + 1) % Block::Scale <= 1) || ((py + 1) % Block::Scale <= 1))
				Screen::SetPixel(px, py, Block::Colors[type][1]);
			else
				Screen::SetPixel(px, py, Block::Colors[type][0]);
		}
}

void Main()
{
	Set((Block::Type *)board, Block::None, Board::Size);

	ulong pFrame = 0;
	while (true)
	{
		ulong now = Time::GetTime();
		if (now - pFrame > Time::Tps)
		{
			pFrame = now;
			if (current)
			{
				if (current->DoesFit(current->x, current->y + 1, current->rot))
					current->y++;
				else
					current->Place();
			}
			else
			{
				// TODO: Optimize
				for (uint i = 0; i < NUM_BLOCKS; i++)
					if (!blocks[i].alive)
					{
						blocks[i] = { true, Board::Width / 2 - 2, 1, System::Random(4), System::Random(Block::Count), };
						current = &blocks[i];
						break;
					}
			}
		}

		Screen::Clear(0x13);
		Draw();
		if (current)
			current->Draw();
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
		if (current->DoesFit(current->x - 1, current->y, current->rot))
			current->x--;
		break;
	case Key::RightArrow:
		if (current->DoesFit(current->x + 1, current->y, current->rot))
			current->x++;
		break;
	case Key::DownArrow:
		if (current->DoesFit(current->x, current->y + 1, current->rot))
			current->y++;
		else
			current->Place();
		break;
	case Key::R:
	{
		int tryRot = current->rot;
		if (Keyboard::mods & Key::Mod::Shift)
		{
			tryRot--;
			if (tryRot < 0)
				tryRot = 3;
		}
		else
			tryRot = (tryRot + 1) % 4;

		if (current->DoesFit(current->x, current->y, tryRot))
			current->rot = tryRot;
		break;
	}
	}}

void KeyRelease(KeyCode keyCode, word mods)
{}