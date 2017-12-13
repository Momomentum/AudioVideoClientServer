TARGET = stream_serv
LIBS = -lm
CC = gcc
SUFFIX = c
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags gstreamer-1.0)
LDFLAGS=$(shell pkg-config --libs gstreamer-1.0)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.$(SUFFIX), %.o, $(wildcard *.$(SUFFIX)))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LDFLAGS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
