CC := gcc
CFLAGS := -Wall -O3 -std=c99

SOURCES := $(shell ls ./*.c)
OBJECTS := $(SOURCES:%.c=%.o)


tileblaster: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(OBJECTS): $(SOURCES)

clean:
	rm -rf $(OBJECTS) tileblaster
