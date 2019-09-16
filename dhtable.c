#include "dhtable.h"
#include "fhtable.h"
#include "helper.h"

#include <stdlib.h>
#include <stdio.h>

#define DHTABLE_GROWTH_FACTOR 2

static void dhtable_rehash(struct dhtable *ht);

/******************************************************************************/

struct dhtable *dhtable_new(unsigned long capacity, double load_factor,
			    unsigned long (*hash_func)(const char*))
{
	struct dhtable *ht;

	ht = malloc(sizeof(struct dhtable));
	ht->load_factor = load_factor;
	ht->hash_func = hash_func;
	ht->primary = fhtable_new(capacity, load_factor, hash_func);

	return ht;
}

void dhtable_free(struct dhtable *ht)
{
	if (!ht)
		return;

	fhtable_free(ht->primary);
	free(ht);
}

void dhtable_set(struct dhtable *ht, const char *key, const char *value)
{
	if (!fhtable_set(ht->primary, key, value)) {
		dhtable_rehash(ht);
		fhtable_set(ht->primary, key, value);
	}
}

struct string *dhtable_get(struct dhtable *ht,  const char *key)
{
	return fhtable_get(ht->primary, key);
}

unsigned long dhtable_size(const struct dhtable *ht)
{
	return fhtable_size(ht->primary);
}

unsigned long dhtable_capacity(const struct dhtable *ht)
{
	return fhtable_capacity(ht->primary);
}

void dhtable_dump(const struct dhtable *ht, unsigned long level)
{
	indent(level);
	printf("Dynamic Hash Table {\n");

	indent(level + 1);
	printf("Load factor: %f\n", ht->load_factor);

	indent(level + 1);
	printf("Primary:\n");
	fhtable_dump(ht->primary, level + 2);

	indent(level);
	printf("}\n");
}

/******************************************************************************/

static void dhtable_rehash(struct dhtable *ht)
{
	unsigned long new_capacity;
	struct fhtable *tmp_fhtable;
	unsigned long i;

	new_capacity = DHTABLE_GROWTH_FACTOR * fhtable_capacity(ht->primary);
	tmp_fhtable = fhtable_new(new_capacity, ht->load_factor, ht->hash_func);

	for (i = 0; i < fhtable_capacity(ht->primary); ++i)
		fhtable_move(tmp_fhtable, ht->primary, i);

	fhtable_free(ht->primary);
	ht->primary = tmp_fhtable;
}
