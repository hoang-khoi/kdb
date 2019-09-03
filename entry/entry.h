#ifndef ENTRY_H
#define ENTRY_H

/*
 * An entry consists of a key and a value.
 */
struct entry {
	void *key;
	void *value;
};

struct entry *entry_new(void *key, void *value);
/*
 * Deallocates an entry with its key and value if deallocator is provided.
 */
void entry_free(struct entry *e, void (*deallocator)(void*));

void *entry_get_key(const struct entry *e);
void *entry_get_value(const struct entry *e);

#endif
