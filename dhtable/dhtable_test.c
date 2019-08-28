#include "dhtable.c"
#include "../fhtable/fhtable.c"
#include "../list/list.c"
#include "../list_string_entry/list_string_entry.c"
#include "../string_entry/string_entry.c"
#include "../entry/entry.c"
#include "../formatter/formatter.c"
#include "../string/string.c"

/*
 * Mock hash function for a string. Returns the value of first character.
 */
unsigned long hash(const char *str)
{
	return *str - '0';
}

int main()
{
	struct dhtable *ht = dhtable_new(4, 0.75, hash);
	dhtable_free(ht);
}
