ARCH       :=i386
TARGET     :=i586-elf-
KRNARCHDIR :=kernel/arch/$(ARCH)/
KLIBCDIR   :=lib/klibc/

AS        :=$(TARGET)as
LD		   :=$(TARGET)gcc
CC		   :=$(TARGET)gcc
CPP		   :=$(TARGET)g++
EMU        :=qemu-system-$(ARCH)

ASFLAGS    :=-Isysroot/usr/include
LDFLAGS	   :=-ffreestanding -O2 -nostdlib -lgcc
CFLAGS	   :=-std=gnu99 -ffreestanding -O2 -Wall -Iinclude -nostdlib -lgcc -Isysroot/usr/include -D$(ARCH)
EMUFLAGS   :=-kernel

DESTDIR    :=sysroot
PREFIX     :=/usr
BOOTDIR    :=/boot
INCLUDEDIR :=$(PREFIX)/include

LINKER     :=$(KRNARCHDIR)link.ld
KRNOBJS    :=$(KRNARCHDIR)head.o kernel/kernel.o $(KRNARCHDIR)screen.o $(KRNARCHDIR)string.o kernel/kprintf.o
#KLIBCOBJS  :=$(KLIBCDIR)stdio/printf.o $(KLIBCDIR)stdio/putchar.o $(KLIBCDIR)stdio/puts.o
#KLIBCOBJS  :=$(KLIBCOBJS) $(KLIBCDIR)stdlib/abort.o $(KLIBCDIR)string/memcmp.o $(KLIBCDIR)string/memcpy.o $(KLIBCDIR)string/memmove.o $(KLIBCDIR)string/memset.o $(KLIBCDIR)string/strlen.o
KRNFILE    :=$(DESTDIR)$(BOOTDIR)/kernel-$(ARCH).elf

all: install kernel test


install: install-headers

install-headers:
	@mkdir -p $(DESTDIR)$(INCLUDEDIR)
	@cp -RTv include $(DESTDIR)$(INCLUDEDIR)



clean:
	-@rm $(KRNOBJS) $(KLIBCOBJS) $(KRNFILE)
	
kernel: $(KRNOBJS) $(KLIBCOBJS) link

.s.o:
	$(AS) $(ASFLAGS) -o $*.o $<
		
.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<
	
link:
	-@mkdir $(DESTDIR)$(BOOTDIR)
	$(LD) -T $(LINKER) -o $(KRNFILE) $(LDFLAGS) $(KRNOBJS) $(KLIBCOBJS)
	
	
test:
	@$(EMU) $(EMUFLAGS) $(KRNFILE)
	

