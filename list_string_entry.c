#include "list_string_entry.h"
#include <stdlib.h>

/*
 * Given a key, return the desired list's iterator.
 */
static struct node *_list_string_entry_find_iterator(const struct list *l,
						     const char *key);

/******************************************************************************/

void list_string_entry_free(struct list *l)
{
	list_free(l, string_entry_free);
}

struct entry *list_string_entry_find(const struct list *l, const char *key)
{
	struct node *it = _list_string_entry_find_iterator(l, key);

	if (!it)
		return NULL;

	return list_iterator_value(it);
}

void list_string_entry_del(struct list *l, const char *key)
{
	struct node *it = _list_string_entry_find_iterator(l, key);

	if (!it)
		return;

	list_del(l, it, string_entry_free);
}

/******************************************************************************/

static struct node *_list_string_entry_find_iterator(const struct list *l,
						    const char *key)
{
	struct node *it = list_begin(l);
	struct entry *e;

	while (list_next(it)) {
		e = list_iterator_value(it);

		if (string_entry_key_equals(e, key))
			return it;

		it = list_next(it);
	}

	return NULL;

}
