#include "../adhtable.c"

#include "../fhtable.c"
#include "../list.c"
#include "../list_string_entry.c"
#include "../string_entry.c"
#include "../entry.c"
#include "../string.c"
#include "../helper.c"

#include <assert.h>

/*
 * Mock hash function for a string. Returns the value of first character.
 */
unsigned long hash(const char *str)
{
	return *str - '0';
}

void test_set()
{
	struct adhtable *ht = adhtable_new(4, 0.75, hash);

	adhtable_set(ht, "0. Key", "Value 0");
	adhtable_set(ht, "4. Key", "Value 1");
	adhtable_set(ht, "1. Key", "Value 3");

	assert(!ht->secondary);
	assert(string_equals(fhtable_get(ht->primary, "0. Key"), "Value 0"));
	assert(string_equals(fhtable_get(ht->primary, "4. Key"), "Value 1"));
	assert(string_equals(fhtable_get(ht->primary, "1. Key"), "Value 3"));

	adhtable_set(ht, "6. Key", "Value 4");

	assert(!fhtable_get(ht->primary, "0. Key"));
	assert(!fhtable_get(ht->primary, "4. Key"));

	assert(string_equals(fhtable_get(ht->secondary, "0. Key"), "Value 0"));
	assert(string_equals(fhtable_get(ht->secondary, "4. Key"), "Value 1"));
	assert(string_equals(fhtable_get(ht->secondary, "6. Key"), "Value 4"));

	assert(8 == fhtable_capacity(ht->secondary));

	assert(1 == ht->migration_idx);

	adhtable_set(ht, "7. Key", "Value 5");

	assert(!ht->secondary);
	assert(string_equals(fhtable_get(ht->primary, "7. Key"), "Value 5"));

	assert(0 == ht->migration_idx);

	assert(5 == adhtable_size(ht));

	adhtable_free(ht);
}

void test_get()
{
	struct adhtable *ht = adhtable_new(4, 0.75, hash);

	adhtable_set(ht, "0. Key", "Value 0");
	adhtable_set(ht, "4. Key", "Value 1");
	adhtable_set(ht, "1. Key", "Value 3");

	assert(string_equals(adhtable_get(ht, "1. Key"), "Value 3"));

	adhtable_set(ht, "6. Key", "Value 4");

	assert(!adhtable_get(ht, "99. Key"));

	assert(!ht->secondary);

	assert(string_equals(adhtable_get(ht, "0. Key"), "Value 0"));
	assert(string_equals(adhtable_get(ht, "4. Key"), "Value 1"));
	assert(string_equals(adhtable_get(ht, "1. Key"), "Value 3"));
	assert(string_equals(adhtable_get(ht, "6. Key"), "Value 4"));

	assert(4 == adhtable_size(ht));

	adhtable_free(ht);
}

int main()
{
	test_set();
	test_get();

	return 0;
}
