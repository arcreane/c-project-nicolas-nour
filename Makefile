CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC = gtk_main.c function.c huffman.c

OBJS = $(SRC:.c=.o)

all: build

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

build: $(OBJS)
	$(CC) -o $(@F) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f build
