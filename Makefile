MODULES=boot driver examples
INCLUDES=common driver
CC=xtensa-lx106-elf-gcc
CFLAGS=-Wall -Wextra -Werror -I./src
LDFLAGS=-nostdlib -nostartfiles -T esp8266.ld
PORT=/dev/tty.usbserial-0001
SRC_DIR=src
BUILD_DIR=build
BAUD=115200
CHIP=esp8266
OUT=main.out
CFILES=$(foreach MOD,$(MODULES),$(wildcard $(SRC_DIR)/$(MOD)/*.c))
OBJECTS=$(patsubst %.c,$(BUILD_DIR)/%.o,$(CFILES))

all:
	make compile
	make image
	make flash

compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(OUT) $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -ffreestanding -c -o $@ $<

image:
	esptool.py -c $(CHIP) elf2image $(BUILD_DIR)/$(OUT) -o $(BUILD_DIR)/$(OUT)

flash:
	esptool.py -c $(CHIP) -p $(PORT) write_flash -fm qio 0x0000 $(BUILD_DIR)/$(OUT)0x00000.bin

print:
	@echo "$(OBJECTS)"
	@echo "$(CFLAGS)"

clean:
	rm -rf build
