#ifndef LIST_STRING_ENTRY
#define LIST_STRING_ENTRY

#include "../list/list.h"
#include "../string_entry/string_entry.h"

/*
 * Specific APIs for list of entries.
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

/*
 * Dumps a list of string entries to stdout for debugging.
 */
void list_string_entry_dump(const struct list *l, int level);

#endif
