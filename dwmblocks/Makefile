.POSIX:

PREFIX = /usr/local
CC = gcc
BINDIR = $(DESTDIR)$(PREFIX)/bin
SCRIPTS = bin/volume bin/mic bin/wpctl-vol bin/brightness bin/cpu \
          bin/memory bin/internet bin/bluetooth bin/battery bin/clock bin/fanspeed

dwmblocks: dwmblocks.o
	$(CC) dwmblocks.o -lX11 -lXft -o dwmblocks

dwmblocks.o: dwmblocks.c config.h
	$(CC) -Wall -Wextra -Wno-unused-parameter -c dwmblocks.c

clean:
	rm -f *.o *.gch dwmblocks

install: dwmblocks
	mkdir -p $(BINDIR)
	cp -f dwmblocks $(BINDIR)/
	chmod 755 $(BINDIR)/dwmblocks
	cp -f bin/icons bin/dwmblocks-lib $(BINDIR)/
	chmod 644 $(BINDIR)/icons
	chmod 755 $(BINDIR)/dwmblocks-lib
	for s in $(SCRIPTS); do \
		cp -f $$s $(BINDIR)/$$(basename $$s); \
		chmod 755 $(BINDIR)/$$(basename $$s); \
	done

uninstall:
	rm -f $(BINDIR)/dwmblocks $(BINDIR)/icons $(BINDIR)/dwmblocks-lib
	for s in $(SCRIPTS); do rm -f $(BINDIR)/$$(basename $$s); done

.PHONY: clean install uninstall
