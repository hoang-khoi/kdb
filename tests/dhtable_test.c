#include "../dhtable.c"

#include "../fhtable.c"
#include "../helper.c"
#include "../list_string_entry.c"
#include "../list.c"
#include "../string_entry.c"
#include "../entry.c"
#include "../string.c"

#include <assert.h>

/*
 * Mock hash function for a string. Returns the value of first character.
 */
unsigned long hash(const char *str)
{
	return *str - '0';
}

/*
 * Main objective to test is the expansion feature.
 */
int main()
{
	struct dhtable *ht = dhtable_new(4, 0.75, hash);

	dhtable_set(ht, "4. Key", "Value 0");
	dhtable_set(ht, "5. Key", "Value 1");
	dhtable_set(ht, "6. Key", "Value 2");

	assert(4 == dhtable_capacity(ht));
	assert(3 == dhtable_size(ht));

	dhtable_set(ht, "7. Key", "Value 3");

	assert(8 == dhtable_capacity(ht));
	assert(4 == dhtable_size(ht));

	dhtable_free(ht);

	return 0;
}
