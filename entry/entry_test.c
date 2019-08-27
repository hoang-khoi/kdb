#include "entry.c"
#include <assert.h>

int main()
{
	void *key = malloc(16);
	void *value = malloc(32);

	struct entry *e = entry_new(key, value, 32);

	// Test data getters
	assert(key == entry_get_key(e));
	assert(value == entry_get_value(e));
	assert(32 == entry_get_hash(e));

	entry_free(e, free);
}
