typedef enum
{
	PALETTE_Mask = 0x3C6,
	PALETTE_Read,
	PALETTE_Write,
	PALETTE_Data,
} Palette;

typedef enum
{
	false,
	true,
} bool;

#ifndef asm
#define asm __asm__ volatile
#endif

static inline void OutPortB(unsigned short port, unsigned char data) {
    asm("outb %1, %0" : : "dN" (port), "a" (data));
}

void ScreenInit()
{
	OutPortB(PALETTE_Mask, 0xFF);
	OutPortB(PALETTE_Write, 0);
	for (int i = 0; i < 255; i++)
	{
        OutPortB(PALETTE_Data, (((i >> 5) & 0x7) * (256 / 8)) / 4);
        OutPortB(PALETTE_Data, (((i >> 2) & 0x7) * (256 / 8)) / 4);
        OutPortB(PALETTE_Data, (((i >> 0) & 0x3) * (256 / 4)) / 4);
    }

    // Set color 255 to white
    OutPortB(PALETTE_Data, 0x3F);
    OutPortB(PALETTE_Data, 0x3F);
    OutPortB(PALETTE_Data, 0x3F);
}

void Main(int magic)
{
	ScreenInit();

	unsigned char *vgaBuff = (unsigned char *)0xA0000;
	for (int i = 0; i < 320*200; i++)
		vgaBuff[i] = i % 256;

	while (true);
}