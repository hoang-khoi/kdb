#include "dhtable.c"
#include "../fhtable/fhtable.c"
#include "../list/list.c"
#include "../list_string_entry/list_string_entry.c"
#include "../string_entry/string_entry.c"
#include "../entry/entry.c"
#include "../formatter/formatter.c"
#include "../string/string.c"

#include <assert.h>

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

	// Test internal data
	assert(hash == ht->hash_func);
	assert(0.75 == ht->load_factor);
	assert(0 == dhtable_size(ht));
	assert(ht->primary);
	assert(!ht->secondary);

	dhtable_free(ht);
}
