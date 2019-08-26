#include "fhtable.c"
#include "../list/list.c"
#include "../string/string.c"
#include "../entry/entry.c"
#include "../string_entry/string_entry.c"
#include "../list_string_entry/list_string_entry.c"

#include <assert.h>

/*
 * Mock hash function for a string. Returns the value of first character.
 */
unsigned long hash(const char *str)
{
	return str[0];
}

int main()
{
	struct fhtable *ht = fhtable_new(0.75, hash);

	// Test initial data
	assert(hash == ht->hash);
	assert(6 == ht->limit);
	assert(8 == ht->capacity);
	assert(0 == ht->size);

	fhtable_free(ht);
}
