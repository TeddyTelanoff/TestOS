.code16
.org 0
.section .text

.global Boot
Boot:
	cli

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

	// Load kernel into mermory at 0x1000 (seg,emt 0x1000)
	// Kernel bin is right after first sector
	// Num sectors to read in %cx

	mov $0x40, %cx
	movw $0x1000, segment
	movw $0, offset
	movw $1, sector
	movw $2, chsSector
	
SectorLoop:
	push %cx

	// Attempt read with "extended read sectors from drive" %ah: 0x42
	mov $0x42, %ah
	mov driveNum, %dl
	mov $diskPacket, %si
	int $0x13
	jnc DiskSuccess

	// Fallback to CHS "read sectors from drive" %ah: 0x2
	mov $0x2, %ah
	mov $1, %al
	mov chsCylinder, %ch
	mov chsSector, %cl
	mov driveNum, %dl
	mov chsHead, %dh
	mov segment, %es
	mov offset, %bx
	int $0x13
	jc DiskError

DiskSuccess:
	incb sector
	incb chsSector

	mov sectorsPerTrack, %al
	cmp %al, chsSector
	jna SectorSameHeadCylinder

	// Sectors per track exceeded, reset sector to 1, increase heads and check for head limit
	movb $1, chsSector
	incb chsHead
	mov numHeads, %al
	cmp %al, chsHead
	jna SectorSameHeadCylinder

	// Head count exceeded, reset head to 0, increase cylinder
	movb $0, chsHead
	incb chsCylinder

SectorSameHeadCylinder:
	// Single sector read, increase offset by 0x200 (512)
	addw $0x200, offset
	jnc SectorSameSegment

	// Increament segment, reset offset if on another segment
	addw $0x1000, segment
	movw $0, offset

SectorSameSegment:
	pop %cx
	loop SectorLoop

	// Video mode: 320x200 @16 cols
	mov $0, %ah
	mov $0x13, %al
	int $0x10

	// Enable A20 line
	cli

	// Read and save state
	call EnableA20Wait0
	mov $0xD0, %al
	outb $0x64
	call EnableA20Wait1
	xor %ax, %ax
	inb $0x60

	// Write new state with A20 bit set (0x2)
	push %ax
	call EnableA20Wait0
	mov $0xD1, %al
	outb $0x64
	call EnableA20Wait0
	pop %ax
	or $0x2, %ax
	outb $0x60

	// Enable PE flag
	mov %cr0, %eax
	or $0x1, %eax
	mov %eax, %cr0

Flush:
	lidt idt
	lgdt gdtp

	mov $(gdtDataSegment - gdtStart), %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	mov $0x3000, %esp
	ljmp $0x8, $Entry32

.code32
Entry32:
	// Jump to kernel loaded at 0x1000
	mov $0x1000, %eax
	jmp *%eax

Loop:
	jmp Loop

.code16
EnableA20Wait0:
	xor %ax, %ax
	inb $0x64
	bt $1, %ax
	jc EnableA20Wait0
	ret

EnableA20Wait1:
	xor %ax, %ax
	int $0x64
	bt $0, %ax
	jnc EnableA20Wait1
	ret

DiskError:
	mov $diskErrorMsg, %si

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

welcomeMsg:
	.string "Good Morning Ninjago!\r\n"
diskErrorMsg:
	.string "Disk Error!\r\n"


chsSector:
	.byte 0
chsCylinder:
	.byte 0
chsHead:
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
diskPacket:
	.byte 0x10
	.byte 0

// GDT
.align 16
gdtp:
	.word gdtEnd - gdtStart - 1
	.long gdtStart

.align 16
gdtStart:
gtdNull:
	.quad 0
gdtDataSegment:
	.word 0xFFFF
	.word 0
	.byte 0
	.byte 0b10010010
	.byte 0b11001111
	.byte 0
gdtEnd:

idt:
	.word 0
	.long 0

.fill 510-(.-Boot), 1, 0
.word 0xAA55
