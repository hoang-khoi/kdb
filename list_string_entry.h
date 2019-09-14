#ifndef LIST_STRING_ENTRY
#define LIST_STRING_ENTRY

#include "list.h"
#include "string_entry.h"

/*
 * Specific APIs for list of entries.
 */

/*
 * Frees the list and all its elements
 */
void list_string_entry_free(struct list *l);
/*
 * Given a key, searches and returns the entry that matches the provided key.
 * Returns NULL if not found.
 */
struct entry *list_string_entry_find(const struct list *l, const char *key);
/*
 * Deletes an entry from the list given its key.
 */
void list_string_entry_del(struct list *l, const char *key);

#endif
