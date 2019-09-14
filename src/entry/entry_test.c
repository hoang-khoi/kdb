#include "entry.c"

#include <assert.h>
#include <string.h>

int main()
{
	void *key = malloc(16);
	void *value = malloc(32);

	strcpy(key, "7.key");

	struct entry *e = entry_new(key, value);

	// Test data getters
	assert(key == entry_get_key(e));
	assert(value == entry_get_value(e));

	entry_free(e, free);
}
