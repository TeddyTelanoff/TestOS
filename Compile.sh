as src/Boot.S -o bin/Boot.o
ld bin/Boot.o -e Boot --oformat binary -o bin/Boot.bin -Ttext 0x7C00