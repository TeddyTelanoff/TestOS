.code16

.global Main
Main:
	call Test
	ret

.fill 510-(.-Main), 1, 0
