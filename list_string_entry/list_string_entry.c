#include "list_string_entry.h"

void list_string_entry_free(struct list *l)
{
	list_free(l, string_entry_free);
}

void list_string_entry_add(struct list *l, const char *key, const char *value)
{
	list_add(l, string_entry_new(key, value));
}

struct string *list_string_entry_get_value(const struct list *l, const char *key)
{
	// TODO
}

void list_string_entry_del(struct list *l, const char *key)
{
	// TODO
}
