CFLAGS=-c -Wall -Wextra -Werror -Wfatal-errors -ansi -pedantic -O2

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
