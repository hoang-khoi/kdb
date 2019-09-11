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

void test_general()
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

void test_set()
{
	struct dhtable *ht = dhtable_new(4, 0.75, hash);

	// Test dhtable_set()
	dhtable_set(ht, "0. Key", "Value 0");
	dhtable_set(ht, "4. Key", "Value 1");
	dhtable_set(ht, "1. Key", "Value 3");

	// Expect those keys are in primary and secondary is now just NULL
	assert(!ht->secondary);
	assert(string_equals(fhtable_get(ht->primary, "0. Key"), "Value 0"));
	assert(string_equals(fhtable_get(ht->primary, "4. Key"), "Value 1"));
	assert(string_equals(fhtable_get(ht->primary, "1. Key"), "Value 3"));

	dhtable_set(ht, "6. Key", "Value 4");

	// Expect 0 and 4 in primary is gone
	assert(!fhtable_get(ht->primary, "0. Key"));
	assert(!fhtable_get(ht->primary, "4. Key"));

	// Expect 0, 4 and 6 is in secondary
	assert(string_equals(fhtable_get(ht->secondary, "0. Key"), "Value 0"));
	assert(string_equals(fhtable_get(ht->secondary, "4. Key"), "Value 1"));
	assert(string_equals(fhtable_get(ht->secondary, "6. Key"), "Value 4"));

	// Expect secondary's capacity is doubled
	assert(8 == fhtable_capacity(ht->secondary));

	// Expect migration index is updated
	assert(1 == ht->migration_idx);

	dhtable_set(ht, "7. Key", "Value 5");

	// Expect slot 1 in primary is moved, primary becomes empty and will
	// be deallocated, then point to secondary.
	assert(!ht->secondary);
	assert(string_equals(fhtable_get(ht->primary, "7. Key"), "Value 5"));

	// Expect migration index is reset
	assert(0 == ht->migration_idx);

	dhtable_free(ht);
}

void test_get()
{
	struct dhtable *ht = dhtable_new(4, 0.75, hash);

	// Test dhtable_set()
	dhtable_set(ht, "0. Key", "Value 0");
	dhtable_set(ht, "4. Key", "Value 1");
	dhtable_set(ht, "1. Key", "Value 3");

	// Expect to get existing key
	assert(string_equals(dhtable_get(ht, "1. Key"), "Value 3"));

	// Now secondary is created.
	dhtable_set(ht, "6. Key", "Value 4");

	// Expect NULL from a non-existing key
	assert(!dhtable_get(ht, "99. Key"));

	// Expect secondary is migrated already.
	assert(!ht->secondary);

	// Check for all keys
	assert(string_equals(dhtable_get(ht, "0. Key"), "Value 0"));
	assert(string_equals(dhtable_get(ht, "4. Key"), "Value 1"));
	assert(string_equals(dhtable_get(ht, "1. Key"), "Value 3"));
	assert(string_equals(dhtable_get(ht, "6. Key"), "Value 4"));

	dhtable_free(ht);
}

int main()
{
	test_general();
	test_set();
	test_get();
}
