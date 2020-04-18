.PHONY : install-headers install  #TODO: Perhaps use -MD with nasm to generate dependency files

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

BOOT_BIN:=	stage1/stage1.bin stage2/stage2.bin

	
install: $(BOOT_BIN)
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $^ $(DESTDIR)$(BOOTDIR)  #TODO: Timestamps? -R?

install-headers:

		
%.bin : %.asm
	nasm $^ -f bin -o $@

clean :
	rm -f $(BOOT_BIN)
