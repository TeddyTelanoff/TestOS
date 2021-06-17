#include "Kernel/Screen.h"
#include "Kernel/System.h"
#include "Kernel/Time.h"
#include "Kernel/Keyboard.h"
#include "Kernel/Font.h"
#include "Kernel/Screen.h"
#include "Kernel/Sound.h"

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
		Stone,

		TrueCount = Z + 1,
		Count = Stone + 1,
		None,
	};

	static const constexpr byte Colors[Types::Count][2] = {
		0x4F, 0x37,
		0x09, 0x20,
		0x2A, 0x06,
		0x0E, 0x74,
		0x2F, 0x02,
		0x0D, 0x05,
		0x28, 0x04,
		0x19, 0x07,
	};

	static const constexpr word Tetriminos[Types::TrueCount][4] = {
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
bool started;
bool medusa;
uint score;
Block current;
static char keyCodeStr[3], scoreStr[16]; 
byte toDestroy[Board::Height];
Block::Type board[Board::Height][Board::Width];

static uint startX = Screen::Width / 2 - Board::Width * Board::Scale / 2, endX = Screen::Width / 2 + Board::Width * Board::Scale / 2;
static uint startY = 0, endY = Board::Height * Board::Scale;

bool Block::DoesFit(int x, int y, int rot) const
{
	for (int ty = 0; ty < Size; ty++)
		for (int tx = 0; tx < Size; tx++)
		{
			int rx = x + tx, ry = y + ty;
			if (BitAt(Tetriminos[type][rot], tx + ty * Size))
			{
				if (rx < 0 || rx >= Board::Width)
					return false;
				if (ry >= Board::Height)
					return false;
				if (ry < 0)
					continue;
				if (board[ry][rx] != Block::None)
					return false;
			}
		}
	
	return true;
}

void MedusaTwo()
{ Sound::Beep(350, Time::Tps / 2); }

void Block::Place()
{
	current.alive = false;

	for (int ty = 0; ty < Size; ty++)
		for (int tx = 0; tx < Size; tx++)
			if (BitAt(Tetriminos[type][rot], tx + ty * Size))
				board[y + ty][x + tx] = type;

	for (uint y = 0; y < Board::Height; y++)
	{
		bool rmedusa = true;
		toDestroy[y] = true;
		for (uint x = 0; x < Board::Width; x++)
			if (board[y][x] != Block::Stone)
			{
				rmedusa = false;
				if (board[y][x] == Block::None)
				{
					toDestroy[y] = false;
					break;
				}
			}

		if (rmedusa = toDestroy[y])
		{
			medusa = true;
			Sound::Beep(370, Time::Tps / 2);
			Time::Schedule(MedusaTwo, Time::Tps / 2);
			return;
		}

		if (toDestroy[y])
			Sound::Beep(87);
	}

	
	for (uint x = 0; x < Board::Width; x++)
	{
		bool inTheDark = false;
		for (uint y = 0; y < Board::Height; y++)
		{
			if (board[y][x] != Block::None)
			{
				if (y > 0 && inTheDark && board[y - 1][x] == Block::None)
					board[y][x] = Block::Stone;
				inTheDark = true;
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
			Block::Type type = board[ty][tx];
			if (type == Block::None)
			{
				if (((px + 1) % Block::Scale <= 1) || ((py + 1) % Block::Scale <= 1))
					Screen::SetPixel(px, py, 0x08);
				continue;
			}

			if (((px + 1) % Block::Scale <= 1) || ((py + 1) % Block::Scale <= 1))
				Screen::SetPixel(px, py, Block::Colors[type][!(medusa || toDestroy[ty])]);
			else
				Screen::SetPixel(px, py, Block::Colors[type][medusa || toDestroy[ty]]);
		}
}

void Restart();

void DestroyToDestroy()
{
	bool destroyed = false;

	// If you do a Medusa, you deserve it
	if (medusa)
	{
		destroyed = true;
		Set((Block::Type *)board, Block::None, Board::Size);
		medusa = false;
		score += 1337;
	}

	for (uint y = 0; y < Board::Height; y++)
	{
		if (!toDestroy[y])
			continue;

		destroyed = true;

		// To prevent, ya know...stuff
		toDestroy[y] = false;
		score += 100;

		if (y != 0)
		{
			for (uint dy = y; dy; dy--)
			{
				for (uint x = 0; x < Board::Width; x++)
					if (board[dy - 1][x] != Block::Stone && board[dy][x] != Block::Stone)
						board[dy][x] = board[dy - 1][x];
			}
		}
		else
			for (uint x = 0; x < Board::Width; x++)
				if (board[y][x] != Block::Stone)
					board[y][x] = Block::None;
	}

	if (destroyed)
	{
		Font::FNum(score, scoreStr);
		Sound::Beep(44, Time::Tps / 2);
	}
}

void Update()
{
	DestroyToDestroy();

	if (current.alive)
	{
		if (current.DoesFit(current.x, current.y + 1, current.rot))
			current.y++;
		else
			current.Place();
	}
	else
	{
		current = { true, Board::Width / 2 - 2, -4, System::Random(4), System::Random(Block::TrueCount), };
		if (!current.DoesFit(current.x, current.y, current.rot))
		{
			System::Log("You Lost :(", Time::Tps * 2);
			Restart();
		}
	}

	Time::Schedule(Update, Time::Tps);
}

void Shake()
{
	for (int i = 0; i < Screen::Size; i++)
	{
		int j = (i + System::Random<int>(2) - 1) % Screen::Size;
		if (j < 0)
			j = Screen::Size - 1;
		Screen::pixels[i] = Screen::pixels[j];
	}
}

void Main()
{
	Set((Block::Type *)board, Block::None, Board::Size);

	while (!started)
	{
		Screen::Clear(0x13);
		const char msg[] = "Press 'enter' to start...";
		Font::DrawStr(msg, Screen::Width / 2 - (sizeof(msg) - 1) * 4, Screen::Height / 2 + 15);
		Screen::SwapBuffers();
	}
	
	Time::Schedule(Update, Time::Tps);	
	while (true)
	{
		Screen::Clear(0x13);
		Draw();
		if (current.alive)
		{
			current.Draw();

			static char buff[2];
			Font::FNum(current.type, buff);
			Font::DrawStr(buff, 5, Screen::Height - 28);
		}
		Font::DrawStr(keyCodeStr, 5, Screen::Height - 13);
		Font::DrawStrDoubled("Score:", 5, 5);
		Font::DrawStrW(scoreStr, 5, 20, startX - 5);
		Shake();
		// PostProcessing();
		Screen::SwapBuffers();
	}
}

void KeyPress(KeyCode keyCode, word mods)
{
	Font::FNum<0x10>(keyCode, keyCodeStr);

	if (!started && keyCode == Key::Enter)
	{
		started = true;
		System::randSeed = Time::GetTime();

		static char buff[16];
		Font::FNum(System::randSeed, buff, true);
		return;
	}

	if (!current.alive)
		return;

	switch (keyCode)
	{
	case Key::M:
		Sound::ToggleMute();
		break;

	case Key::A:
	case Key::LeftArrow:
		if (current.DoesFit(current.x - 1, current.y, current.rot))
			current.x--;
		break;
	case Key::D:
	case Key::RightArrow:
		if (current.DoesFit(current.x + 1, current.y, current.rot))
			current.x++;
		break;
	case Key::S:
	case Key::DownArrow:
		if (current.DoesFit(current.x, current.y + 1, current.rot))
			current.y++;
		break;
	case Key::W:
	case Key::UpArrow:
	case Key::R:
	{
		if (mods & (Key::Mod::Ctrl | Key::Mod::Alt))
			Restart();

		int tryRot = current.rot;
		if (mods & Key::Mod::Shift)
		{
			tryRot--;
			if (tryRot < 0)
				tryRot = 3;
		}
		else
			tryRot = (tryRot + 1) % 4;

		if (current.DoesFit(current.x, current.y, tryRot))
			current.rot = tryRot;
		break;
	}
	}}

void KeyRelease(KeyCode keyCode, word mods)
{}

void Restart()
{
	current.alive = false;
	Set((Block::Type *)board, Block::None, Board::Size);
}