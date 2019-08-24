#include "string_entry.h"

struct entry *string_entry_new(const char *key, const char *value)
{
	return entry_new(string_new(key), string_new(value));
}

void string_entry_free(struct entry *e)
{
	entry_free(e, (void*) string_free);
}
