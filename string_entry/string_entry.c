#include "string_entry.h"
#include <stdio.h>

struct entry *string_entry_new(const char *key,
			       const char *value,
			       unsigned long (*hash_func)(const char*))
{
	return entry_new(string_new(key), string_new(value), hash_func(key));
}

void string_entry_free(void *e)
{
	entry_free(e, (void*) string_free);
}

int string_entry_key_equals(const struct entry *e, const char *buffer)
{
	return string_equals(entry_get_key(e), buffer);
}

void string_entry_dump(const struct entry *e)
{
	printf("Entry: {\n");

	printf("\tKey: ");
	string_dump(e->key);

	printf("\tValue: ");
	string_dump(e->value);

	printf("\tHash: %lu\n", e->hash);

	printf("}\n");
}
