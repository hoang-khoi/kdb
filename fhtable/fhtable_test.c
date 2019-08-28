#include "fhtable.c"
#include "../list/list.c"
#include "../string/string.c"
#include "../entry/entry.c"
#include "../string_entry/string_entry.c"
#include "../list_string_entry/list_string_entry.c"
#include "../formatter/formatter.c"

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
	struct fhtable *ht = fhtable_new(8, 0.75, hash);

	// Test initial data
	assert(hash == ht->hash_func);
	assert(6 == ht->limit);
	assert(8 == ht->capacity);
	assert(0 == ht->size);

	// Trying to add some entries
	char *keys[6] = {"0", "1", "2", "3", "4", "5"};
	char *values[6] = {"Hoang", "Khoi", "Dep", "Trai", "Vai", "Chuong"};

	for (int i = 0; i < 6; ++i)
		assert(fhtable_add(ht, keys[i], values[i]));

	// Limit reached, should not accept any record
	assert(!fhtable_add(ht, "Denied", "How sad"));

	// Check entries location
	for (int i = 0; i < 6; ++i) {
		struct list *chain = ht->chains[i];
		struct entry *e = list_string_entry_find(chain, keys[i]);
		assert(string_entry_key_equals(e, keys[i]));

	}

	// Trying to get values
	for (int i = 0; i < 6; ++i) {
		struct string *value_string = fhtable_get(ht, keys[i]);
		assert(string_equals(value_string, values[i]));
	}

	// Trying to get a key that does not exist
	assert(!fhtable_get(ht, "Denied"));

	fhtable_dump(ht, 0);

	fhtable_free(ht);
}
