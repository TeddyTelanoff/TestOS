#include "Kernel/Screen.h"
#include "Kernel/System.h"
#include "Kernel/Time.h"


#include "Kernel/Screen.h"

struct Obj
{
	bool alive;
	float x, y;
	void (*DrawFn)(const Obj *);
	void (*UpdateFn)(Obj *);

	void Draw()
	{
		if (alive)
			DrawFn(this);
	}

	void Update()
	{
		if (alive)
			UpdateFn(this);
	}

	void Destroy()
	{ alive = false; }
};

struct Box
{
	enum Data
	{
		Width = 9,
		Height = 9,
		Scale = 4,
	};

	static constexpr byte Texture[Width][Height] = {
		{ 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, },
		{ 0x72, 0x72, 0x06, 0x06, 0x06, 0x06, 0x06, 0x72, 0x72, },
		{ 0x72, 0x06, 0x72, 0x06, 0x06, 0x06, 0x72, 0x06, 0x72, },
		{ 0x72, 0x06, 0x06, 0x72, 0x06, 0x72, 0x06, 0x06, 0x72, },
		{ 0x72, 0x06, 0x06, 0x06, 0x72, 0x06, 0x06, 0x06, 0x72, },
		{ 0x72, 0x06, 0x06, 0x72, 0x06, 0x72, 0x06, 0x06, 0x72, },
		{ 0x72, 0x06, 0x72, 0x06, 0x06, 0x06, 0x72, 0x06, 0x72, },
		{ 0x72, 0x72, 0x06, 0x06, 0x06, 0x06, 0x06, 0x72, 0x72, },
		{ 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, },
	};
};

void BoxDraw(const Obj *This)
{
	for (int py = 0; py < Box::Height * Box::Scale; py++)
		for (int px = 0; px < Box::Width * Box::Scale; px++)
			Screen::SetPixel(This->x * Box::Scale + px, This->y * Box::Scale + py, Box::Texture[px / Box::Scale][py / Box::Scale]);
}

void BoxUpdate(Obj *This)
{
	This->y += 0.3f;
	if (This->y * Box::Scale >= Screen::Height)
		This->Destroy();
}

Obj objects[64] {};

void Main()
{
	ulong pFrame = 0;
	while (true)
	{
		ulong now = Time::GetTime();
		if (now - pFrame > 1)
		{
			pFrame = now;
			for (uint i = 0; i < 64; i++)
			{
				objects[i].Update();
				if (!objects[i].alive && System::Random<bool>())
					objects[i] = { true, System::Random<float>(Screen::Width / Box::Scale), -Box::Height, BoxDraw, BoxUpdate, };
			}
		}

		Screen::Clear(0x13);
		for (uint i = 0; i < 64; i++)
			objects[i].Draw();
		Screen::SwapBuffers();
	}
}