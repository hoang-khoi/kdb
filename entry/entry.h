#ifndef ENTRY_H
#define ENTRY_H

/*
 * This is the basic unit to hold key-value data in a hash table.
 */

struct entry {
	void *key;
	void *value;
};

/*
 * Create a new generic entry.
 */
struct entry *entry_new(void *key, void *value);
/*
 * Deallocates an entry with its key and value, if deallocator is provided.
 */
void entry_free(struct entry *e, void (*deallocator)(void*));
/*
 * Get key's pointer.
 */
void *entry_get_key(const struct entry *e);
/*
 * Get value's pointer.
 */
void *entry_get_value(const struct entry *e);

#endif
