UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
	CC=g++ -elf_i386
	AS=as --32
	LD=ld -m elf_i386
else
	CC=i386-elf-g++
	AS=i386-elf-as
	LD=i386-elf-ld
endif

GFLAGS=
CCFLAGS=-m32 -std=c++2a -O2 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CCFLAGS+=-Wno-pointer-arith -Wno-unused-parameter -Wno-unused-function
CCFLAGS+=-nostdlib -nostdinc -ffreestanding -fno-pie -fno-stack-protector
CCFLAGS+=-fno-builtin-function -fno-builtin
CCFLAGS+=-I src
ASFLAGS=
LDFLAGS=

BOOTSECT_SRCS=src/Boot.S

BOOTSECT_OBJS=$(BOOTSECT_SRCS:.S=.o)

ifeq ($(game),tetris)
GAME_SRCS=src/Games/Tetris.cpp
else ifeq ($(game),gtn)
GAME_SRCS=src/Games/GuessTheNumber.cpp
else ifeq ($(game),50subz)
GAME_SRCS=src/Games/50subz.cpp
else
$(error Must choose a game to boot)
endif

KERNEL_CPP_SRCS=$(wildcard src/Kernel/*.cpp)
KERNEL_S_SRCS=$(wildcard src/Kernel/*.S)
KERNEL_OBJS=$(KERNEL_CPP_SRCS:.cpp=.o) $(KERNEL_S_SRCS:.S=.o) $(GAME_SRCS:.cpp=.o)

BOOTSECT=Boot.bin
KERNEL=Kernel.bin
IMG=Boot.img

all: clean img finish

clean:
	rm -f ./**/*.o
	rm -f ./**/**/*.o
	rm -f ./*.img
	rm -f ./**/*.elf
	rm -f ./*.iso
	rm -f ./**/*.bin

finish:
	rm -f ./**/*.o
	rm -f ./**/**/*.o
	rm -f ./**/*.bin

%.o: %.cpp
	$(CC) -o $@ -c $< $(GFLAGS) $(CCFLAGS)

%.o: %.S
	$(AS) -o $@ -c $< $(GFLAGS) $(ASFLAGS)

dirs:
	mkdir -p bin

bootsect: $(BOOTSECT_OBJS)
	$(LD) -o ./bin/$(BOOTSECT) $^ -Ttext 0x7C00 --oformat=binary -e Boot

kernel: $(KERNEL_OBJS)
	$(LD) -o ./bin/$(KERNEL) $^ $(LDFLAGS) -Tsrc/Kernel/Link.ld

img: dirs bootsect kernel
	dd if=/dev/zero of=$(IMG) bs=512 count=2880
	dd if=./bin/$(BOOTSECT) of=$(IMG) conv=notrunc bs=512 seek=0 count=1
	dd if=./bin/$(KERNEL) of=$(IMG) conv=notrunc bs=512 seek=1 count=2048

iso: clean img finish
	mkisofs -pad -b $(IMG) -R -o Boot.iso $(IMG)

qemu-mac: img
	qemu-system-i386 -drive format=raw,file=$(IMG) -d cpu_reset -monitor stdio -device sb16 -audiodev coreaudio,id=coreaudio,out.frequency=48000,out.channels=2,out.format=s32

qemu-pulse: img
	qemu-system-i386 -drive format=raw,file=$(IMG) -d cpu_reset -monitor stdio -device sb16 -audiodev pulseaudio,id=pulseaudio,out.frequency=48000,out.channels=2,out.format=s32

qemu-sdl: img
	qemu-system-i386 -display sdl -drive format=raw,file=$(IMG) -d cpu_reset -monitor stdio -audiodev sdl,id=sdl,out.frequency=48000,out.channels=2,out.format=s32 -device sb16,audiodev=sdl

qemu-no-audio: img
	qemu-system-i386 -drive format=raw,file=$(IMG) -d cpu_reset -monitor stdio

