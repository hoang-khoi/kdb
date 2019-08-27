#include "string_entry.h"
#include "../formatter/formatter.h"

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

void string_entry_dump(const struct entry *e, int level)
{
	formatter_indent(level);
	printf("Entry: {\n");

	formatter_indent(level + 1);
	printf("Key: ");
	string_dump(e->key, 0);

	formatter_indent(level + 1);
	printf("Value: ");
	string_dump(e->value, 0);

	formatter_indent(level + 1);
	printf("Hash: %lu\n", e->hash);

	formatter_indent(level);
	printf("}\n");
}
