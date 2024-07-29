MODULES=boot driver examples
INCLUDES=common driver
CC=xtensa-lx106-elf-gcc
CFLAGS=-Os -Wall -Wextra -Werror -mlongcalls -mtext-section-literals -I./src
LDFLAGS=-nostdlib -nostartfiles -T esp8266.ld
PORT=/dev/tty.usbserial-0001
SRC_DIR=src
BUILD_DIR=build
BAUD=115200
CHIP=esp8266
OUT=main.out

CFILES   = $(foreach MOD,$(MODULES),$(wildcard $(SRC_DIR)/$(MOD)/*.c))
SFILES   = $(foreach MOD,$(MODULES),$(wildcard $(SRC_DIR)/$(MOD)/*.s))
OBJECTS  = $(patsubst %.c,$(BUILD_DIR)/%.o,$(CFILES))
OBJECTSS = $(patsubst %.s,$(BUILD_DIR)/%_s.o,$(SFILES))

all:
	make compile
	make image
	make flash

compile: $(OBJECTS) $(OBJECTSS)
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/$(OUT) $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -ffreestanding -c -o $@ $<

$(BUILD_DIR)/%_s.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -ffreestanding -c -o $@ $<

image:
	esptool.py -c $(CHIP) elf2image $(BUILD_DIR)/$(OUT) -o $(BUILD_DIR)/$(OUT)

flash:
	esptool.py -b $(BAUD) -c $(CHIP) -p $(PORT) write_flash -z -ff 40m -fm qio 0x0000 $(BUILD_DIR)/$(OUT)0x00000.bin

print:
	@echo "$(OBJECTS)"
	@echo "$(OBJECTSS)"
	@echo "$(CFLAGS)"
	@echo "$(SLIBS)"

clean:
	rm -rf build
