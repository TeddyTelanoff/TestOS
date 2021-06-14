.code32
.section .text.prologue

.global KernelMain
KernelMain:
	mov $stack, %esp
	and $-16, %esp
	push %esp
	call Main
	cli
	hlt
	jmp KernelMain

.size KernelMain, . - KernelMain

.section .data
.align 32
stack_start:
	.fill 0x4000
stack:
