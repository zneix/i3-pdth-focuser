.PHONY: build

PREFIX := /usr/local/bin

#CFLAGS := $(shell pkg-config --cflags i3ipc-glib-1.0)
#LDFLAGS := $(shell pkg-config --libs i3ipc-glib-1.0)
CFLAGS_LDFLAGS := $(shell pkg-config --cflags --libs i3ipc-glib-1.0)

SOURCES := main.c
EXECUTABLE := pdth-focuser

default: build

compile_flags:
	@echo "$(CFLAGS_LDFLAGS)" | sed -e 's/ /\n/g' > compile_flags.txt

build: compile_flags
	gcc $(CFLAGS_LDFLAGS) $(SOURCES) -o $(EXECUTABLE)

install: build
	cp $(EXECUTABLE) $(PREFIX)/$(EXECUTABLE)

uninstall:
	rm $(PREFIX)/$(EXECUTABLE)

clean:
	rm $(EXECUTABLE)
