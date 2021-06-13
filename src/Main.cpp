using PaletteEnum = unsigned short;
namespace Palette
{
enum: PaletteEnum
{
	Mask = 0x3C6,
	Read,
	Write,
	Data,
};
}

#ifndef asm
#define asm __asm__ volatile
#endif

static inline void OutPortB(unsigned short port, unsigned char data) {
    asm("outb %1, %0" : : "dN" (port), "a" (data));
}

static inline void ScreenInit()
{
	OutPortB(Palette::Mask, 0xFF);
	OutPortB(Palette::Write, 0);
	for (unsigned char i = 0; i < 255; i++)
	{
        OutPortB(Palette::Data, (((i >> 5) & 0x7) * (256 / 8)) / 4);
        OutPortB(Palette::Data, (((i >> 2) & 0x7) * (256 / 8)) / 4);
        OutPortB(Palette::Data, (((i >> 0) & 0x3) * (256 / 4)) / 4);
    }

    // Set color 255 to white
    OutPortB(Palette::Data, 0x3F);
    OutPortB(Palette::Data, 0x3F);
    OutPortB(Palette::Data, 0x3F);
}

extern "C" void Main(int magic)
{
	ScreenInit();

	unsigned char *vgaBuff = (unsigned char *)0xA0000;
	for (int i = 0; i < 320*200; i++)
		vgaBuff[i] = 255;

	while (true);
}