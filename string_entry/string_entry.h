#ifndef STRING_ENTRY_H
#define STRING_ENTRY_H

#include "../string/string.h"
#include "../entry/entry.h"

/*
 * Specific APIs for string key-value entries.
 */

struct entry *string_entry_new(const char *key, const char *value);
void string_entry_free(void *e);

#endif
