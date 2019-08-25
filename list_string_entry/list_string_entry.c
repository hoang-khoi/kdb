#include "list_string_entry.h"
#include <stdlib.h>

void list_string_entry_free(struct list *l)
{
	list_free(l, string_entry_free);
}

void list_string_entry_add(struct list *l, const char *key, const char *value)
{
	list_add(l, string_entry_new(key, value));
}

struct entry *list_string_entry_find(const struct list *l, const char *key)
{
	struct node *it = list_begin(l);
	struct entry *e;

	while ((it = list_next(it))) {
		e = list_iterator_value(it);

		if (string_entry_key_equals(e, key))
			return e;
	}

	return NULL;
}

void list_string_entry_del(struct list *l, const char *key)
{
	// TODO
}
