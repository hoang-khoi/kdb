#include "dhtable.h"
#include <stdlib.h>

struct dhtable *dhtable_new(unsigned long capacity,
			    double load_factor,
			    unsigned long (*hash_func)(const char*))
{
	struct dhtable *ht = malloc(sizeof(struct dhtable));
	ht->hash_func = hash_func;
	ht->size = 0;
	ht->primary = fhtable_new(capacity, load_factor, hash_func);
	ht->secondary = NULL;

	return ht;
}

void dhtable_free(struct dhtable *ht)
{
	if (!ht)
		return;

	fhtable_free(ht->primary);
	fhtable_free(ht->secondary);

	free(ht);
}
