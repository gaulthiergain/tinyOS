OBJECTS = 	multiboot.o gdt.o lgdt.o loader.o io.o serial.o fb.o kmain.o keyboard.o	\
			lidt.o interrupt_handler.o idt.o	pic.o common.o paging.o kheap.o enable_paging.o
CC = gcc
CFLAGS = 	-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -DDEBUG=3
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
	qemu-system-x86_64 -enable-kvm -cdrom os.iso -curses -chardev stdio,id=char0,logfile=serial.log,signal=off -serial chardev:char0 -monitor telnet:127.0.0.1:55555,server,nowait;

run-qemu-debug:	os.iso
	qemu-system-x86_64 -enable-kvm -s -S /dev/zero -cdrom os.iso -serial stdio -curses -monitor telnet:127.0.0.1:55555,server,nowait;

run-bochs: os.iso	
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rfv *.o kernel.elf os.iso
