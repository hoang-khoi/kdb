#include "string_entry.h"

struct entry *string_entry_new(const char *key, const char *value)
{
	return entry_new(string_new(key), string_new(value));
}

void string_entry_free(void *e)
{
	entry_free(e, (void*) string_free);
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
