#include "dhtable.h"
#include "../formatter/formatter.h"

#include <stdlib.h>
#include <stdio.h>

#define DHTABLE_GROWTH_FACTOR 2

/* Private APIs */

void _dhtable_set_secondary(struct dhtable *ht, const char *key,
			    const char *value);
void _dhtable_set_primary(struct dhtable *ht, const char *key,
			  const char *value);
void _dhtable_init_secondary(struct dhtable *ht);
/*
 * Move a chain from primary to secondary.
 */
void _dhtable_migrate(struct dhtable *ht);

/******************************************************************************/

struct dhtable *dhtable_new(unsigned long capacity,
			    double load_factor,
			    unsigned long (*hash_func)(const char*))
{
	struct dhtable *ht = malloc(sizeof(struct dhtable));
	ht->hash_func = hash_func;
	ht->load_factor = load_factor;
	ht->primary = fhtable_new(capacity, load_factor, hash_func);
	ht->secondary = NULL;

	ht->migration_idx = 0;

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

void dhtable_set(struct dhtable *ht, const char *key, const char *value)
{
	if (ht->secondary)
		_dhtable_set_secondary(ht, key, value);
	else
		_dhtable_set_primary(ht, key, value);
}

unsigned long dhtable_size(const struct dhtable* ht)
{
	unsigned long size = fhtable_size(ht->primary);

	if (ht->secondary)
		size += fhtable_size(ht->secondary);

	return size;
}

void dhtable_dump(const struct dhtable *ht, int level)
{
	printf("Dynamic Hash Table {\n");


	formatter_indent(level + 1);
	printf("Load Factor: %f\n", ht->load_factor);

	formatter_indent(level + 1);
	printf("Primary:\n");
	fhtable_dump(ht->primary, level + 2);

	formatter_indent(level + 1);
	printf("Secondary:\n");
	fhtable_dump(ht->secondary, level + 2);

	formatter_indent(level + 1);
	printf("Migration Index: %lu\n", ht->migration_idx);

	printf("}\n");
}

/******************************************************************************/

void _dhtable_set_secondary(struct dhtable *ht, const char *key,
			    const char *value)
{
	fhtable_set(ht->secondary, key, value);
	_dhtable_migrate(ht);
}

void _dhtable_set_primary(struct dhtable *ht, const char *key,
			  const char *value)
{
	if (!fhtable_set(ht->primary, key, value)) {
		_dhtable_init_secondary(ht);
		_dhtable_set_secondary(ht, key, value);
	}
}

void _dhtable_init_secondary(struct dhtable *ht)
{
	unsigned long pri_cap = fhtable_capacity(ht->primary);
	unsigned long sec_cap = pri_cap * DHTABLE_GROWTH_FACTOR;

	ht->secondary = fhtable_new(sec_cap, ht->load_factor, ht->hash_func);
}

void _dhtable_migrate(struct dhtable *ht)
{
	fhtable_move(ht->secondary, ht->primary, ht->migration_idx++);

	if (fhtable_is_empty(ht->primary)) {
		ht->migration_idx = 0;
		fhtable_free(ht->primary);
		ht->primary = ht->secondary;
		ht->secondary = NULL;
	}
}
