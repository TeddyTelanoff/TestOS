.code16
.org 0
.text

.global Boot
Boot:
	// Setup segments
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

	// Move stack ptr to free mem area
	mov $0x3000, %sp

	// Save drive num to read kernel later
	mov %dl, driveNum
	sti

	mov $welcomeMsg, %si
	call Print
	
	// Read drive params, INT 0x13 %ah: 0x8
	mov $8, %ah
	mov driveNum, %dl
	int $0x13

	mov %dh, numHeads
	and $0x4F, %cl
	mov %cl, sectorsPerTrack

	// Load kernel into mermory at 0x10000 (seg,emt 0x1000)
	// Kernel bin is right after first sector
	// Num sectors to read in %cx

	mov $0x40, %cx
	movw $0x10000, segment
	movw $0, offset
	movw $1, sector
	movw $2, chsSector
	
SectorLoop:
	push %cx

	// Attempt read with "extended read sectors from drive" %ah: 0x42
	mov $0x42, %ah
	mov driveNum, @dl
	mov $diskPacket, %si
	int $0x13
	jnc DiskSuccess

	// Fallback to CHS "read sectors from drive" %ah: 0x2
	mov $0x2, %ah
	mov $1, %al
	mov chsCylinder, %ch
	mov chsSector, %cl
	mov driveNum, %dl
	


Print:
	xor %bh, %bh
	mov $0x0E, %ah
	lodsb

	// Null check
	cmp $0, %al
	je StopPrint

	// Print %al to screen
	int $0x10
	jmp Print
StopPrint:
	ret

.rodata
welcomeMsg:
	.string "Good Morning Ninjago!\r\n"

.bss
chsSector:
	.byte 0
driveNum:
	.byte 0
numHeads:
	.byte 0
sectorsPerTrack:
	.byte 0
segment:
	.word 0
sector:
	.word 0
offset:
	.word 0

.fill 510-(.-Boot), 1, 0
.word 0xAA55
