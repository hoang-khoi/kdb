#include "fhtable.h"
#include <stdlib.h>

struct fhtable *fhtable_new(unsigned long capacity,
			    double load_ratio,
			    unsigned long (*hash_func)(const char*))
{
	struct fhtable *ht = malloc(sizeof(struct fhtable));

	ht->hash_func = hash_func;
	ht->capacity = capacity;
	ht->limit = load_ratio * ht->capacity;
	ht->size = 0;

	ht->chains = malloc(ht->capacity * sizeof(void*));
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

char fhtable_add(struct fhtable * ht,
		 const char *key,
		 const char *value)
{
	if (ht->size >= ht->limit)
		return 0;

	struct entry *e = string_entry_new(key, value, ht->hash_func);
	unsigned long chain_idx = entry_get_hash(e) % ht->capacity;

	list_add(ht->chains[chain_idx], e);

	++ht->size;
	return 1;
}
