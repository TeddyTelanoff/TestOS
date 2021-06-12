as src/Boot.S -o bin/Boot.o
as src/Kernel.S -o bin/Kernel.o
ld -T src/Link.ld -o bin/TestOS.bin bin/Boot.o bin/Kernel.o -Ttext 0x7C00