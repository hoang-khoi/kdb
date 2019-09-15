#ifndef STRING_ENTRY_H
#define STRING_ENTRY_H

#include "string.h"
#include "entry.h"

/*
 * Specific APIs for string key-value entries.
 */

/*
 * Creates a new key-value entry.
 */
struct entry *string_entry_new(const char *key, const char *value);
/*
 * Frees a key-value entry.
 */
void string_entry_free(void *e);
/*
 * Returns 1 if the entry's key equals to buffer, 0 otherwise.
 */
int string_entry_key_equals(const struct entry *e, const char *buffer);
/*
 * Returns entry key's hash value.
 */
unsigned long string_entry_hash(const struct entry *e,
				unsigned long (*hash_func)(const char*));
/*
 * Dumps string entry to stdout for debugging.
 */
void string_entry_dump(const struct entry *e, int level);

#endif
