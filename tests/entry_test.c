#include "../entry.c"

#include <assert.h>
#include <string.h>

int main()
{
	void *key = malloc(16);
	void *value = malloc(32);
	struct entry *e;

	strcpy(key, "7.key");

	e = entry_new(key, value);

	assert(key == entry_get_key(e));
	assert(value == entry_get_value(e));

	entry_free(e, free);

	return 0;
}
