CSTD            ?= -std=c99

TGT_CFLAGS	+= -I. -I./libs $(CSTD)
TGT_CXXFLAGS	+= -I. -I./libs

BINARY		= tests
SRCFILES	= tests.c

TOCHECK := $(wildcard *.c *.h *.cpp *.cxx)
TOCHECK += $(wildcard libs/*.c libs/*.h libs/*.cpp libs/*.cxx)


SRC_EXT = c

# tool macros
CC := gcc
CCFLAG := -std=c99 -I. -DUNITTEST
DBGFLAG := -g
CCOBJFLAG := $(CCFLAG) -c
LDFLAGS := -lc -lgcc

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug

# compile macros
TARGET_NAME := tests
TARGET := $(TARGET_NAME)
MAIN_SRC := tests.c

OBJS = $(SRCFILES:%.$(SRC_EXT)=%.o)
DEPS = $(OBJECTS:.o=.d)

# default rule
default: clean all

# non-phony targets
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	./$(TARGET)

%.o: %.c*
	echo $(CCOBJFLAG)
	$(CC) $(CCOBJFLAG) -o $(*).o -c $(*).c

# check sources. -$(CSTD) translate -std=... to --std=...
check:
	cppcheck -q --enable=all -$(CSTD) --check-config --includes-file=mk/cppcheck.includes $(TOCHECK)
	vera++ --exclusions mk/vera++.excl -s -e $(TOCHECK)

clean:
	@#printf "  CLEAN\n"
	$(RM) *.o *.d generated.* $(OBJS) $(patsubst %.o,%.d,$(OBJS)) $(patsubst %.o,%.su,$(OBJS))
	$(RM) *.elf *.bin *.hex *.srec *.list *.map tests tests.su
	$(RM) -r docs

# phony rules
.PHONY: all
all: $(TARGET)
