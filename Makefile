.PHONY : all
all: marmite marmite-app

CC := clang -std=c11
CFLAGS := $(shell pkg-config --cflags vte-2.90 gtk+-3.0 glib-2.0 )
LDLIBS := $(shell pkg-config --libs vte-2.90 gtk+-3.0 glib-2.0 )

palette.h: make-palette
	./make-palette > palette.h

look.o: look.c palette.h

marmite: marmite.c args.o look.o

marmite-app: marmite-app.c

test: t
	$(MAKE) -C t
	prove -v

.PHONY : clean
clean:
	$(MAKE) -C t clean
	rm marmite marmite-app make-palette
