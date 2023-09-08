CC = gcc
CFLAGS = -Wall -I/usr/include/libnl3 -I/usr/include/libnl3/genl
LDFLAGS = -L/usr/lib -lnl-genl-3 -lnl-3

all: main

main: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f main
