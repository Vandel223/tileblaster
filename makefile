CC := gcc
CFLAGS := -Wall -g -std=c99

SOURCES := $(shell ls ./*.c)
OBJECTS := $(SOURCES:%.c=%.o)


teste1: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(OBJECTS): $(SOURCES)

clean:
	rm -rf $(OBJECTS) teste1
