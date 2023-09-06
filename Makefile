TARGET ?= blink

# Detect if we are in Windows or in Linux
ifeq ($(OS),Windows_NT)
	RMDIR := rd /s /q
else
	RMDIR := rm -rf
endif

BUILD_DIR = build

# Stuff to compile drivers static library
DRIVERS_DIR := drivers
DRIVERS_SRC := $(wildcard $(DRIVERS_DIR)/src/*)
DRIVERS_OBJ := $(DRIVERS_SRC:.c=.o)
DRIVERS_LIB := libdrivers.a

# Select sources
TARGETS_DIR = apps
SRCS = $(TARGETS_DIR)/$(TARGET)/main.c
#SRCS += $(DRIVERS_SRC)

# Create object files names
OBJS =  $(addsuffix .o, $(basename $(SRCS)))

# Linker script and libraries include
INCLUDES = -I. -I$(DRIVERS_DIR)/inc/
LINKER_SCRIPT = stm32.ld

CFLAGS += -mcpu=cortex-m3 -mthumb # Processor setup
CFLAGS += -O2 # Optimization ON
CFLAGS += -g2 # Generate debug info
CFLAGS += -fno-common
CFLAGS += -Wall # Turn on warnings
#CFLAGS += -pedantic # more warnings
CFLAGS += -Wsign-compare
CFLAGS += -mfloat-abi=soft -fsingle-precision-constant
CFLAGS += -Wcast-align
#CFLAGS += -Wconversion # neg int const implicitly converted to uint
CFLAGS += -fomit-frame-pointer # Do not use fp if not needed
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS += -march=armv7-m
LDFLAGS += -nostartfiles
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,--gc-sections # Linker garbage collector
LDFLAGS += -T$(LINKER_SCRIPT)

CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size
DBG = $(CROSS_COMPILE)gdb

.PHONY: all build build_lib size clean flash debug ocd-start

## Compile app
all: clean $(DRIVERS_LIB) $(SRCS) build size
	@echo "Successfully finished..."

build: $(BUILD_DIR) $(TARGET).elf $(TARGET).hex $(TARGET).bin

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET).elf: $(OBJS) $(DRIVERS_LIB)
	@echo "Building application elf: "\
		"$(addprefix $(BUILD_DIR)/, $(OBJS)) -> $(BUILD_DIR)/$@..."
	@mkdir -p $(BUILD_DIR)/$(TARGET)
	$(CC) $(addprefix $(BUILD_DIR)/, $(OBJS)) $(LDFLAGS) $(INCLUDES) \
		-o $(BUILD_DIR)/$(TARGET)/$@ \
		$(BUILD_DIR)/$(DRIVERS_LIB)

## Library
build_drivers: $(DRIVERS_LIB)

$(DRIVERS_LIB): $(DRIVERS_OBJ)
	@echo "Building static library with the drivers ($<)..."
	ar rcs $(BUILD_DIR)/$(DRIVERS_LIB) \
		$(addprefix $(BUILD_DIR)/, $(DRIVERS_OBJ))

## Auto-rules to compile stuff
%.o: %.c
	@echo "Building $<\t($< -> $@)."
	@mkdir -p $(BUILD_DIR)/$(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(BUILD_DIR)/$@

%.hex: %.elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(TARGET)/$< $(BUILD_DIR)/$(TARGET)/$@

%.bin: %.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET)/$< $(BUILD_DIR)/$(TARGET)/$@

size: $(TARGET).elf
	$(SIZE) $(BUILD_DIR)/$(TARGET)/$(TARGET).elf

## Flash and Debug stuff (run build previouslly)
ocd-flash : build
	openocd -f openocd.cfg -c "program $(BUILD_DIR)/$(TARGET)/$(TARGET).bin exit 0x08000000 verify reset exit"

debug:
	@$(DBG) -tui --eval-command="target extended-remote :3333" \
	--eval-command="layout split" \
	--eval-command="break main" \
	--eval-command="monitor reset halt" \
	--eval-command="jump main" \
	 $(BUILD_DIR)/$(TARGET)/$(TARGET).elf

ocd-start:
	openocd -f openocd.cfg

clean:
	@echo "Cleaning..."
	-$(RMDIR) $(BUILD_DIR)


