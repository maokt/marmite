SOURCE := $(wildcard *.t.c)
TARGET := $(basename $(SOURCE))

CC := clang -std=c11
CFLAGS := -g -O0 $(shell pkg-config --cflags tap )
LDLIBS := $(shell pkg-config --libs tap )

.PHONY : all
all: $(TARGET)

.PHONY : clean
clean:
	rm $(TARGET)

