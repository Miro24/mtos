
SETUP = SIMU

PROGRAM = mtos


ifeq ($(findstring SIMU, $(SETUP)), SIMU)
ARCH_GENERIC = simu
TOOLCHAIN = SIMU

else
@echo "Error: not valid value for: SETUP"
exit 1
endif

CURR_DIR := .
MTOS_DIR := $(CURR_DIR)/..
MTOS_SRC_DIR := $(MTOS_DIR)/src
BUILD_DIR  := $(CURR_DIR)/out

SRC_DIRS = $(MTOS_SRC_DIR)/config
SRC_DIRS += $(MTOS_SRC_DIR)/comm
SRC_DIRS += $(MTOS_SRC_DIR)/protocol

# Get full path of C files
C_SRCS = $(shell find $(SRC_DIRS) -maxdepth 1 -name '*.c')
# Get the files without their full path
C_SRCS_ = $(patsubst %.c,%.c,$(notdir $(C_SRCS)))
# Build object files from C files
C_OBJS = $(C_SRCS_:%.c=$(BUILD_DIR)/%.$(C_OBJ_EXT))


#-----
# SIMU
#-----
ifeq ($(findstring SIMU, $(TOOLCHAIN)), SIMU)

CC = gcc
LD = gcc
DEBUGGER := gdb
C_OBJ_FLAG = -c
C_OBJ_EXT = o
ASM_EXT = S
ASM_OBJ_EXT = o
ASM_OBJ_FLAG = -c
OTHERCCFLAGS =
DEBUGFLAG = -g
LDFLAGS = -pthread
BINTOHEX = echo
DEBUG_TOOL_DIR =
DEBUG_TOOL =
DEBUGGERFLAGS :=
PREPRO_EXT = pre
FORMATER = objcopy
FORMATERFLAGS = -O binary
PROGRAM_EXT = .elf
DEBUGFLAG = -g
#CFLAGS += -Wall
CFLAGS +=
ASMFLAGS +=  
PREPROFLAGS += -Wall -E

else ifeq ($(findstring ARM, $(TOOLCHAIN)), ARM)
@echo "Error: not valid value for: SETUP"
exit 1
else
@echo "Error: not valid value for: SETUP"
exit 1
endif

VPATH = $(SRC_DIRS)
CFLAGS = $(SRC_DIRS:%=-I%)
CFLAGS += $(ARCHFLAGS) $(DEBUGFLAG) $(OTHERCFLAGS)

ALL_LIST = $(BUILD_DIR)
ALL_LIST += $(BUILD_DIR)/$(PROGRAM)$(PROGRAM_EXT)

all: $(ALL_LIST) 

view_variables:
	echo "C_SRCS is" $(C_SRCS)
	echo "C_OBJS is" $(C_OBJS)

$(BUILD_DIR):
	mkdir $@

$(C_OBJS): $(BUILD_DIR)/%.$(C_OBJ_EXT): %.c
	$(CC) $(CFLAGS) $(C_OBJ_FLAG) $< -o$@

$(BUILD_DIR)/$(PROGRAM)$(PROGRAM_EXT): $(ASM_OBJS) $(C_OBJS)
	$(LD) $^ -o$@ $(LDFLAGS) -lc -lm

clean:
	rm -f $(BUILD_DIR)/*_asm.o
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/*.elf
	rm -f $(BUILD_DIR)/*.bin
	rm -f $(BUILD_DIR)/*.list
	rm -f $(BUILD_DIR)/*.img
	rm -f $(BUILD_DIR)/*.pre
	rm -f $(BUILD_DIR)/*.hex
	rm -f $(BUILD_DIR)/*.map
	rm -r $(BUILD_DIR)
