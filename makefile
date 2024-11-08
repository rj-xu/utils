# Project
PROJECT := KunLun
CORE := omx148b
TARGET := $(CORE)

USE_LIBC := 1
USE_LIBM := 0

# Workspace
WORKSPACE := $(shell pwd)

SRC_DIR   := src
INC_DIR   := inc
CORE_DIR  := core/$(CORE)
BUILD_DIR := build
LIBS_DIR  := libs
UTILS_DIR := $(SRC_DIR)/utils

OBJ_DIR := $(BUILD_DIR)/obj

CODE_DIRS := $(CORE_DIR) $(SRC_DIR)
CODE_DIRS := $(shell find $(CODE_DIRS) -type d)

CLEAN_LIST := $(BUILD_DIR)

# Target
ELF := $(BUILD_DIR)/$(TARGET).elf
BIN := $(BUILD_DIR)/$(TARGET).bin
MAP := $(BUILD_DIR)/$(TARGET).map

# Binutils
TOOLCHAIN := arm-none-eabi
CC        := $(TOOLCHAIN)-gcc
AR        := $(TOOLCHAIN)-ar
LD        := $(TOOLCHAIN)-ld

OBJCOPY   := $(TOOLCHAIN)-objcopy
OBJDUMP   := $(TOOLCHAIN)-objdump
READELF   := $(TOOLCHAIN)-readelf

NM        := $(TOOLCHAIN)-nm
SIZE      := $(TOOLCHAIN)-size

# Complier
STD_FLAGS := -std=gnu17 -ffreestanding # -fno-builtin -pedantic
DBG_FLAGS := #-g -Og
OPT_FLAGS := -O3 -fdata-sections -ffunction-sections

WARN_FLAGS :=	-Wall -Wextra # -Werror
WARN_FLAGS +=	-Werror=enum-compare \
				-Werror=sizeof-pointer-memaccess \
				-Werror=sizeof-array-argument
WARN_FLAGS +=	-Wno-unused-variable

CC_FLAGS  := $(STD_FLAGS) $(DBG_FLAGS) $(OPT_FLAGS) $(WARN_FLAGS)

# Core
CORE_FLAGS :=	-mcpu=cortex-m4	\
				-mthumb			\
				-mthumb-interwork

CORE_FLAGS +=	-mfpu=fpv4-sp-d16	\
				-mfloat-abi=hard	\
				-fsingle-precision-constant

CC_FLAGS += $(CORE_FLAGS)

# Defines
DEFS :=
DEFS := $(foreach i, $(DEFS), $(addprefix -D, $(i)))
DEFS +=
CC_FLAGS += $(DEFS)

# Includes
INCS := $(CORE_DIR) $(UTILS_DIR) $(SRC_DIR)/reg $(SRC_DIR)/drv
INCS := $(foreach i, $(INCS), $(addprefix -I, $(i)))
INCS +=
CC_FLAGS += $(INCS)

# Libraries
LIBS :=
LIBS := $(foreach i, $(LIBS), $(addprefix -l, $(i)))
LIBS +=
LD_FLAGS += $(LIBS)

# Linker
STARTUP := $(CORE_DIR)/startup_omx148.c
LD_SCRIPT := $(CORE_DIR)/config/omx148_gcc.ld
LD_FLAGS :=	-Map=$(MAP)		\
			-gc-sections	\
			--cref

LD_FLAGS := $(foreach i, $(LD_FLAGS), $(addprefix -Xlinker , $(i)))

ifeq ($(USE_LIBC), 1)
	LD_FLAGS += -specs=nano.specs
	LD_FLAGS += -specs=nosys.specs
	LD_FLAGS += -u _printf_float
else
	LD_FLAGS += -nolibc -nostdlib
endif

LD_FLAGS += -T$(LD_SCRIPT) $(CORE_FLAGS)


# CC_FLAGS += -specs=nano.specs -specs=nosys.specs

# Source Code
SRC_DIRS := $(CODE_DIRS)
SRC_C := $(foreach i, $(SRC_DIRS), $(wildcard $(i)/*.c))
SRC_CXX := $(foreach i, $(SRC_DIRS), $(wildcard $(i)/*.cpp))
SRC := $(SRC_C) $(SRC_CXX)

OBJ_C := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRC_C)))
OBJ_CXX := $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(SRC_CXX)))
OBJ := $(OBJ_C) $(OBJ_CXX)

PREP := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.i, $(SRC)))
ASM := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.s, $(SRC)))

# Make
.PHONY: all
all: $(BIN)

$(BIN): $(ELF)
	@echo "-----------------------"
	@echo "[INFO] Making ..."
	@mkdir -p $(dir $@)
	@$(OBJCOPY) -O binary -S $(ELF) $(BIN)
	@$(READELF) -a $(ELF) > $(ELF).readelf
	@echo "[INFO] Make $(notdir $@) Done"

$(ELF): $(OBJ)
	@echo "-----------------------"
	@echo "[INFO] Linking ..."
	@mkdir -p $(dir $@)
	@$(CC) $(LD_FLAGS) $(OBJ) -o $@
	@echo "[INFO] Link $(notdir $@) Done"

$(OBJ): $(OBJ_DIR)/%.o: %.c
	@echo "-----------------------"
	@echo "[INFO] CC $(notdir $<) ..."
	@mkdir -p $(dir $@)
	@$(CC) -c $(CC_FLAGS) $(C_FLAGS) $< -o $@
	@echo "[INFO] CC $(notdir $@) Done"

.PHONY: prep
prep: $(PREP)
$(PREP): $(OBJ_DIR)/%.i: %.c
	@echo "-----------------------"
	@echo "[INFO] Preprocess $(notdir $<) ..."
	@mkdir -p $(dir $@)
	@$(CC) -E -C $(CC_FLAGS) $< -o $@
	@echo "[INFO] Preprocess $(notdir $@) Done"

.PHONY: asm
asm: $(ASM)
$(ASM): $(OBJ_DIR)/%.s: %.c
	@echo "-----------------------"
	@echo "[INFO] Assemble $(notdir $<) ..."
	@mkdir -p $(dir $@)
	@$(CC) -S -C $(CC_FLAGS) $< -o $@
	@echo "[INFO] Assemble $(notdir $@) Done"

.PHONY: clean
clean:
	@echo "-----------------------"
	@echo "[INFO] Cleaning ..."
	@rm -rf $(CLEAN_LIST)
	@echo "[INFO] Clean Done"

.PHONY: rebuild
rebuild: clean all
	@echo "-----------------------"
	@echo "[INFO] Rebuild Done"

.PHONY: debug
debug:
	@echo "-----------------------"
	@echo $(OBJ)
