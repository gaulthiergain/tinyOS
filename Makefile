OBJECTS = loader.o io.o serial.o fb.o kmain.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf 

all: os.iso

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp -v kernel.elf iso/boot/kernel.elf
	genisoimage -R								\
					-b boot/grub/stage2_eltorito\
					-no-emul-boot               \
					-boot-load-size 4           \
					-A os                       \
					-input-charset utf8         \
					-quiet                      \
					-boot-info-table            \
					-o os.iso                   \
					iso

run: os.iso
	qemu-system-x86_64 -cdrom os.iso -curses -monitor telnet:127.0.0.1:55555,server,nowait;
	#qemu-system-x86_64 -s -S /dev/zero -cdrom os.iso -curses -monitor telnet:127.0.0.1:55555,server,nowait;
	#bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rfv *.o kernel.elf os.iso
