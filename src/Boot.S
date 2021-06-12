.code16

.section .text

.global Boot
Boot:
	mov $0x0e, %ah
	call Test
	ret

Test:
	mov $msg1, %si
	call Print
	mov $msg2, %si
	call Print
	ret

Print:
	lodsb
	
	cmp $0, %al
	je Stop

	int $0x10
	jmp Print

Stop:
	ret

msg1:
	.string "Welcome to the world!\r\n"
msg2:
	.string "Young padowan!\r\n"

.code32
entry32:
	mov $0x10000, %eax
	jmp *%eax

.fill 510-(.-Boot), 1, 0
.word 0xAA55
