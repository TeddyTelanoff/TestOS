.code16

.global Boot
Boot:
	mov $0x0e, %ah

	call Main
	hlt

.global Test
Test:
	mov $msg1, %si
	call Print
	mov $msg2, %si
	call Print
	ret

.global Print
Print:
	lodsb
	
	cmp $0, %al
	je Stop

	int $0x10
	jmp Print

Stop:
	ret

.global msg1
.global msg2
msg1:
	.string "Welcome to the world!\r\n"
msg2:
	.string "Young padowan!\r\n"

.fill 510-(.-Boot), 1, 0
.word 0xAA55
