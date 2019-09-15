CFLAGS=-c -Wall -Wextra -Werror -Wfatal-errors -O2 -std=gnu99

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

benchmark: objects
	$(CC) $(OBJECTS) -o benchmark
%.o: %.c
	$(CC) $(CFLAGS) $<

objects: $(OBJECTS)

clean:
	rm -f *.o benchmark

.PHONY: clean
