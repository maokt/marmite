all: marmite marmite-app
.PHONY : all

CFLAGS := $(shell pkg-config --cflags vte-2.90 gtk+-3.0 glib-2.0 )
LDFLAGS := $(shell pkg-config --libs vte-2.90 gtk+-3.0 glib-2.0 )

marmite: marmite.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

marmite-app: marmite-app.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

clean:
	rm marmite marmite-app

.PHONY : clean
