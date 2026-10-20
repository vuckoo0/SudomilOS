TOOLCHAIN = /usr/local/i386elfgcc/bin
CC = $(TOOLCHAIN)/i386-elf-gcc
LD = $(TOOLCHAIN)/i386-elf-ld
CFLAGS = -ffreestanding -m32 -g -Wall -Wextra -MMD -MP -c
BIN_DIR = Binaries

# Find every .c and .asm file under Kernel/, excluding kernel_entry.asm (handled separately)
C_SOURCES = $(shell find Kernel -name '*.c')
ASM_SOURCES = $(filter-out Kernel/kernel_entry.asm, $(shell find Kernel -name '*.asm'))

C_OBJECTS = $(patsubst Kernel/%.c, $(BIN_DIR)/%.o, $(C_SOURCES))
ASM_OBJECTS = $(patsubst Kernel/%.asm, $(BIN_DIR)/%.o, $(ASM_SOURCES))

-include $(C_OBJECTS:.o=.d)

all: $(BIN_DIR)/OS.bin

$(BIN_DIR):
	mkdir -p $@

$(BIN_DIR)/boot.bin: Bootloader/boot.asm | $(BIN_DIR)
	nasm $< -f bin -o $@

$(BIN_DIR)/zeroes.bin: Bootloader/zeroes.asm | $(BIN_DIR)
	nasm $< -f bin -o $@

$(BIN_DIR)/kernel_entry.o: Kernel/kernel_entry.asm | $(BIN_DIR)
	nasm $< -f elf -o $@

$(BIN_DIR)/%.o: Kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/%.o: Kernel/%.asm
	@mkdir -p $(dir $@)
	nasm $< -f elf -o $@

$(BIN_DIR)/full_kernel.bin: $(BIN_DIR)/kernel_entry.o $(C_OBJECTS) $(ASM_OBJECTS)
	$(LD) -o $@ -Ttext 0x1000 $(BIN_DIR)/kernel_entry.o $(C_OBJECTS) $(ASM_OBJECTS) --oformat binary

$(BIN_DIR)/OS.bin: $(BIN_DIR)/boot.bin $(BIN_DIR)/full_kernel.bin $(BIN_DIR)/zeroes.bin
	cat $(BIN_DIR)/boot.bin $(BIN_DIR)/full_kernel.bin $(BIN_DIR)/zeroes.bin > $@

run: all
	qemu-system-x86_64 -drive format=raw,file=$(BIN_DIR)/OS.bin,index=0,if=floppy -m 128M

clean:
	rm -rf $(BIN_DIR)

.PHONY: all run clean
