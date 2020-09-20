# Simple Makefile - this project is simple we dont need a BIG, OP Makefile

# SHELL
RM := rm -rf
AR := ar rcs

# PRETTY PRINTS
define print_cc
	$(if $(Q), @echo "[CC]        $(1)")
endef

define print_bin
	$(if $(Q), @echo "[BIN]       $(1)")
endef

define print_rm
    $(if $(Q), @echo "[RM]        $(1)")
endef

define print_ar
    $(if $(Q), @echo "[AR]        $(1)")
endef


# ARGS (Quiet OR Verbose), type make V=1 to enable verbose mode
ifeq ("$(origin V)", "command line")
	Q :=
else
	Q ?= @
endif

# DIRS
IDIR := ./inc
ADIR := ./example

SCRIPT_DIR := ./scripts

# FILES
ASRC := $(wildcard $(ADIR)/*.c)

AOBJ := $(ASRC:%.c=%.o)
OBJ := $(AOBJ)

DEPS := $(OBJ:%.o=%.d)

# LIBS remember -l is added automaticly so type just m for -lm
LIB :=

# BINS
AEXEC := example.out

# COMPI, DEFAULT GCC
CC ?= gcc

C_STD   := -std=gnu17
C_OPT   := -O3
C_FLAGS :=
C_WARNS :=

DEP_FLAGS := -MMD -MP
LINKER_FLAGS:= -fPIC

H_INC := $(foreach d, $(IDIR), -I$d)
L_INC := $(foreach l, $(LIB), -l$l)

ifeq ($(CC),clang)
	C_WARNS += -Weverything -Wno-padded
else ifneq (, $(filter $(CC), cc gcc))
	C_WARNS += -Wall -Wextra -pedantic -Wcast-align \
			   -Winit-self -Wlogical-op -Wmissing-include-dirs \
			   -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef  \
			   -Wwrite-strings -Wpointer-arith -Wmissing-declarations \
			   -Wuninitialized -Wold-style-definition -Wstrict-prototypes \
			   -Wmissing-prototypes -Wswitch-default -Wbad-function-cast \
			   -Wnested-externs -Wconversion -Wunreachable-code
endif

ifeq ("$(origin DEBUG)", "command line")
	GGDB := -ggdb3
else
	GGDB :=
endif

INSTALL_PATH =

# Path for install KMacros
ifeq ("$(origin P)", "command line")
  INSTALL_PATH = $(P)
endif

C_FLAGS += $(C_STD) $(C_OPT) $(GGDB) $(C_WARNS) $(DEP_FLAGS) $(LINKER_FLAGS)

all: examples

install: __FORCE
	$(Q)$(SCRIPT_DIR)/install_kmacros.sh $(INSTALL_PATH)


__FORCE:

examples: $(AEXEC)

$(AEXEC): $(AOBJ)
	$(call print_bin,$@)
	$(Q)$(CC) $(C_FLAGS) $(H_INC) $(AOBJ) -o $@ $(L_INC)

%.o:%.c %.d
	$(call print_cc,$<)
	$(Q)$(CC) $(C_FLAGS) $(H_INC) -c $< -o $@

clean:
	$(call print_rm,EXEC)
	$(Q)$(RM) $(AEXEC)
	$(call print_rm,OBJ)
	$(Q)$(RM) $(OBJ)
	$(call print_rm,DEPS)
	$(Q)$(RM) $(DEPS)

help:
	@echo "KMacros Makefile"
	@echo -e
	@echo "Targets:"
	@echo "    all               - build examples"
	@echo "    examples          - build examples"
	@echo "    install[P = Path] - install kmacros to path P or default Path"
	@echo -e
	@echo "Makefile supports Verbose mode when V=1"
	@echo "To check default compiler (gcc) change CC variable (i.e export CC=clang)"

$(DEPS):


include $(wildcard $(DEPS))
