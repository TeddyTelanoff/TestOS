.code32
.section .text.prologue

.global KernelMain
KernelMain:
	mov $stack, %esp
	and $-16, %esp
	push %esp
	call Init

.section .data
.align 32
stack_start:
	.fill 0x4000
stack:
