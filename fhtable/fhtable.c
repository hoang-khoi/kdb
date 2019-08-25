#include "fhtable.h"
#include <stdlib.h>

struct fhtable *fhtable_new(double load_ratio,
			    unsigned long (*hash)(const char*))
{
	struct fhtable *ht = malloc(sizeof(struct fhtable));

	ht->hash = hash;
	ht->capacity = load_ratio * FHTABLE_INIT_CAPACITY;
	ht->size = 0;

	ht->chains = malloc(ht->capacity * sizeof(struct list*));
	for (unsigned long i = 0; i < ht->capacity; ++i)
		ht->chains[i] = list_new();

	return ht;
}

void fhtable_free(struct fhtable *ht)
{
	if (!ht)
		return;

	for (unsigned long i = 0; i < ht->capacity; ++i)
		list_string_entry_free(ht->chains[i]);

	free(ht->chains);
	free(ht);
}
