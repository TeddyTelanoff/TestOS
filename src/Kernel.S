.code32
.section .text.prologue

.global KernelMain
KernelMain:
	mov $stack, %esp
	and $-16, %esp
	mov $0xDEADBEEF, %eax
	push %esp
	push %eax
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
