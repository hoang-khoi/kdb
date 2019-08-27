#include "list_string_entry.h"
#include "../formatter/formatter.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Given a key, return the desired list's iterator.
 */
static struct node *list_string_entry_find_iterator(const struct list *l,
						    const char *key);


/******************************************************************************/

void list_string_entry_free(struct list *l)
{
	list_free(l, string_entry_free);
}

struct entry *list_string_entry_find(const struct list *l, const char *key)
{
	struct node *it = list_string_entry_find_iterator(l, key);

	if (!it)
		return NULL;

	return list_iterator_value(it);
}

void list_string_entry_del(struct list *l, const char *key)
{
	struct node *it = list_string_entry_find_iterator(l, key);

	if (!it)
		return;

	list_del(l, it, string_entry_free);
}

void list_string_entry_dump(const struct list *l, int level)
{
	formatter_indent(level);
	printf("List: {\n");

	formatter_indent(level + 1);
	printf("Size: %lu\n", list_size(l));

	formatter_indent(level + 1);
	printf("Data: {\n");

	struct node *it = list_begin(l);
	while (list_next(it)) {
		string_entry_dump(list_iterator_value(it), level + 2);
		it = list_next(it);
	}

	formatter_indent(level + 1);
	printf("}\n");

	formatter_indent(level);
	printf("}\n");
}

/******************************************************************************/

static struct node *list_string_entry_find_iterator(const struct list *l,
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
