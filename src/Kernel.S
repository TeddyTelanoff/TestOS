.code32

.section .multiboot

.global KernelMain
KernelMain:
	mov $0x69, %eax
	ret

.section .data
.align 32
stack_start:
	.fill 0x4000
stack:
