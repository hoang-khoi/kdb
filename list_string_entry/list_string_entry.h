#ifndef LIST_STRING_ENTRY
#define LIST_STRING_ENTRY

#include "../list/list.h"
#include "../string_entry/string_entry.h"

/*
 * Specific APIs for list of entries.
 */

void list_string_entry_free(struct list *l);
void list_string_entry_add(struct list *l, const char *key, const char *value);
/*
 * Given a key, search through the list and returns the associated value.
 * Returns NULL if not found.
 */
struct string *list_string_entry_get_value(const struct list *l, const char *key);
void list_string_entry_del(struct list *l, const char *key);

#endif
