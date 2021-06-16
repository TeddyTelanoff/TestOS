.code32
.section .text

.global Shutdown
Shutdown:
	mov $0x1000, %ax
	mov %ss, %ax
	mov $0xF000, %sp
	mov $0x5307, %ax
	mov $0x0001, %bx
	mov $0x0003, %cx
	int $0x15
	ret