.code32

.section .multiboot

.global KernelMain
KernelMain:
    mov $stack, %esp
    and $-16, %esp
    mov $0xDEADBEEF, %eax
    push %esp
    push %eax
    
    call Main
	ret

.section .data
.align 32
stack_start:
	.fill 0x4000
stack:
