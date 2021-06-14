.code32
.section .text
.align 4

.global IdtLoad
.type IdtLoad, @function
IdtLoad:
	mov 4(%esp), %eax
	lidt (%eax)
	ret

.macro ISR_NO_ERR index
	.global _isr\index
	_isr\index:
		cli
		push $0
		push $\index
		jmp IsrCommon
.endm

.macro ISR_ERR index
	.global _isr\index
	_isr\index:
		cli
		push $\index
		jmp IsrCommon
.endm

ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR 8
ISR_NO_ERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_NO_ERR 17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_NO_ERR 30
ISR_NO_ERR 31
ISR_NO_ERR 32
ISR_NO_ERR 33
ISR_NO_ERR 34
ISR_NO_ERR 35
ISR_NO_ERR 36
ISR_NO_ERR 37
ISR_NO_ERR 38
ISR_NO_ERR 39
ISR_NO_ERR 40
ISR_NO_ERR 41
ISR_NO_ERR 42
ISR_NO_ERR 43
ISR_NO_ERR 44
ISR_NO_ERR 45
ISR_NO_ERR 46
ISR_NO_ERR 47

// Defined in Isr.cpp
.extern IsrHandler
.type IsrHandler, @function

IsrCommon:
	pusha
	push %ds
	push %es
	push %fs
	push %gs

	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	cld

	push %esp
	call IsrHandler
	add $4, %esp

	pop %gs
	pop %fs
	pop %es
	pop %ds

	popa

	add $8, %esp
	iret