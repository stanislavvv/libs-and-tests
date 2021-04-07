TGT_CFLAGS	+= -I. -I./libs
TGT_CXXFLAGS	+= -I. -I./libs

BINARY		= tests
SRCFILES	= tests.c

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

clean:
	@#printf "  CLEAN\n"
	$(RM) *.o *.d generated.* $(OBJS) $(patsubst %.o,%.d,$(OBJS)) $(patsubst %.o,%.su,$(OBJS))
	$(RM) *.elf *.bin *.hex *.srec *.list *.map tests tests.su
	$(RM) -r docs

# phony rules
.PHONY: all
all: $(TARGET)
