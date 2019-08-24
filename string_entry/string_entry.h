#ifndef STRING_ENTRY_H
#define STRING_ENTRY_H

#include "../string/string.h"
#include "../entry/entry.h"

/*
 * Specific APIs for string key-value entries.
 */

struct entry *string_entry_new(const char *key, const char *value);
void string_entry_free(void *e);
/*
 * Returns 1 if key equals to buffer, 0 otherwise.
 */
int string_entry_key_equals(const struct entry *e, const char *buffer);

#endif
