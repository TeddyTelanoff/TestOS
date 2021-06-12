as src/Boot.S -o bin/Boot.o
as src/Kernel.S -o bin/Kernel.o
gcc -c src/Test.c -o bin/Test.o
ld -o bin/Boot.bin bin/Boot.o -Ttext 0x7C00 -e Boot --oformat binary
ld -T src/Link.ld -o bin/Kernel.bin bin/Kernel.o bin/Test.o
dd if=/dev/zero of=bin/Boot.img bs=512 count=2880
dd if=./bin/Boot.bin of=./bin/Boot.img conv=notrunc bs=512 seek=0 count=1
dd if=./bin/Kernel.bin of=./bin/Boot.img conv=notrunc bs=512 seek=1 count=2048
mkisofs -pad -b bin/Boot.img -R -o bin/Boot.iso bin/Boot.img