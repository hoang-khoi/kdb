#include "string_entry.h"
#include "helper.h"

#include <stdio.h>

struct entry *string_entry_new(const char *key, const char *value)
{
	return entry_new(string_new(key), string_new(value));
}

void string_entry_free(void *e)
{
	entry_free(e, string_free);
}

int string_entry_key_equals(const struct entry *e, const char *buffer)
{
	return string_equals(entry_get_key(e), buffer);
}

unsigned long string_entry_hash(const struct entry *e,
				unsigned long (*hash_func)(const char*))
{
	return string_hash(entry_get_key(e), hash_func);
}

void string_entry_dump(const struct entry *e, int level)
{
	indent(level);
	printf("Entry: {\n");

	indent(level + 1);
	printf("Key: ");
	string_dump(e->key, 0);

	indent(level + 1);
	printf("Value: ");
	string_dump(e->value, 0);

	indent(level);
	printf("}\n");
}
