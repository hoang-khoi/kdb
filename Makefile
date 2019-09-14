CFLAGS=-c -Wall -Wextra -Werror -Wfatal-errors -O2 -std=gnu99
MODULES=dhtable entry fhtable hash list list_string_entry string string_entry\
	benchmark
OBJS=$(MODULES:=.o)

benchmark: objects
	$(CC) $(OBJS) -o benchmark
%.o: %.c
	$(CC) $(CFLAGS) $<

objects: $(OBJS)

clean:
	rm -f *.o benchmark

.PHONY: clean
