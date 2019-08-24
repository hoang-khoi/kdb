#include "entry.c"
#include <assert.h>

int main()
{
	void *key = malloc(16);
	void *value = malloc(32);

	struct entry *e = entry_new(key, value);

	// Test data getters
	assert(key == entry_get_key(e));
	assert(value == entry_get_value(e));

	entry_free(e, free);
}
