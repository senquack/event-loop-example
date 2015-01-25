# Many examples and much inspiration here couresy of:
# Nebuleon and Maarten ter Huurne.

CC          :=  /opt/gcw0-toolchain/usr/bin/mipsel-linux-gcc
STRIP       :=  /opt/gcw0-toolchain/usr/bin/mipsel-linux-strip

SYSROOT     := $(shell $(CC) --print-sysroot)
SDL1_CFLAGS := $(shell $(SYSROOT)/usr/bin/sdl-config --cflags) -DSDL_1
SDL1_LIBS   := $(shell $(SYSROOT)/usr/bin/sdl-config --libs) 
SDL2_CFLAGS := $(shell $(SYSROOT)/usr/bin/sdl2-config --cflags) -DSDL_2
SDL2_LIBS   := $(shell $(SYSROOT)/usr/bin/sdl2-config --libs) 

OBJS        := event-loop-sdl-1.2.o event-loop-sdl-2.o
HEADERS     :=

INCLUDE     := -I.
DEFS        +=

CFLAGS       = -Wall -Wno-unused-variable \
               -O2 $(DEFS) $(INCLUDE)
LDFLAGS     :=

.PHONY: all opk

all: event-loop-sdl-1.2 event-loop-sdl-2

include Makefile.rules

event-loop-sdl-1.2: event-loop-sdl-1.2.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(SDL1_CFLAGS) $(SDL1_LIBS) -o $@ $^

event-loop-sdl-2: event-loop-sdl-2.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(SDL2_CFLAGS) $(SDL2_LIBS) -o $@ $^

event-loop-sdl-1.2.o: event-loop.c
	$(CC) $(CFLAGS) $(SDL1_CFLAGS) -o $@ -c $<

event-loop-sdl-2.o: event-loop.c
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -o $@ -c $<

# The two below declarations ensure that editing a .c file recompiles only that
# file, but editing a .h file recompiles everything.
# Courtesy of Maarten ter Huurne.

# Each object file depends on its corresponding source file.
$(C_OBJS): %.o: %.c

# Object files all depend on all the headers.
$(OBJS): $(HEADERS)
