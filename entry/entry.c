#include "entry.h"
#include <stdlib.h>

struct entry *entry_new(void *key, void *value, unsigned long hash)
{
	struct entry *e = malloc(sizeof(struct entry));
	e->key = key;
	e->value = value;
	e->hash = hash;

	return e;
}

void entry_free(struct entry *e, void (*deallocator)(void*))
{
	if (!e)
		return;

	if (deallocator) {
		deallocator(e->key);
		deallocator(e->value);
	}

	free(e);
}
void *entry_get_key(const struct entry *e)
{
	return e->key;
}

void *entry_get_value(const struct entry *e)
{
	return e->value;
}

unsigned long entry_get_hash(const struct entry *e)
{
	return e->hash;
}
