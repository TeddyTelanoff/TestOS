typedef enum VgaCol VgaCol;

enum VgaCol
{
	VGA_Black,
	VGA_Blue,
	VGA_Green,
	VGA_Cyan,
	VGA_Red,
	VGA_Magenta,
	VGA_Brown,
	VGA_LightGrey,
	VGA_DarkGrey,
	VGA_LightBlue,
	VGA_LightGreen,
	VGA_LightCyan,
	VGA_LightRed,
	VGA_LightMagenta,
	VGA_LightBrown,
	VGA_White,
};

void Main(int magic)
{
	short *vgaBuff = (short *)0xB8000;
	vgaBuff[0] = (short)('T' | (VGA_Green << 8));

	while(1);
}