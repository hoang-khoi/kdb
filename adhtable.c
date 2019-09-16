#include "adhtable.h"
#include "helper.h"

#include <stdlib.h>
#include <stdio.h>

#define DHTABLE_GROWTH_FACTOR 2

/*
 * Sets key-value record to secondary fhtable, then migrate the data
 * internally.
 * This should be called if secondary is present.
 */
void _adhtable_set_secondary(struct adhtable *ht, const char *key,
			    const char *value);
/*
 * Sets key-value record to primary. This is called when secondary fhtable
 * is not initialized.
 */
void _adhtable_set_primary(struct adhtable *ht, const char *key,
			  const char *value);
/*
 * Initializes secondary fhtable with double capacity from primary.
 */
void _adhtable_init_secondary(struct adhtable *ht);
/*
 * Migrates data by moving a chain from primary to secondary.
 */
void _adhtable_migrate(struct adhtable *ht);

/******************************************************************************/

struct adhtable *adhtable_new(unsigned long capacity,
			    double load_factor,
			    unsigned long (*hash_func)(const char*))
{
	struct adhtable *ht = malloc(sizeof(struct adhtable));
	ht->hash_func = hash_func;
	ht->load_factor = load_factor;
	ht->primary = fhtable_new(capacity, load_factor, hash_func);
	ht->secondary = NULL;

	ht->migration_idx = 0;

	return ht;
}

void adhtable_free(struct adhtable *ht)
{
	if (!ht)
		return;

	fhtable_free(ht->primary);
	fhtable_free(ht->secondary);

	free(ht);
}

void adhtable_set(struct adhtable *ht, const char *key, const char *value)
{
	if (ht->secondary)
		_adhtable_set_secondary(ht, key, value);
	else
		_adhtable_set_primary(ht, key, value);
}

struct string *adhtable_get(struct adhtable *ht, const char *key)
{
	struct string *result = fhtable_get(ht->primary, key);

	if (!result && ht->secondary) {
		result = fhtable_get(ht->secondary, key);
		_adhtable_migrate(ht);
	}

	return result;
}

unsigned long adhtable_size(const struct adhtable* ht)
{
	unsigned long size = fhtable_size(ht->primary);

	if (ht->secondary)
		size += fhtable_size(ht->secondary);

	return size;
}

void adhtable_dump(const struct adhtable *ht, unsigned long level)
{
	printf("Dynamic Hash Table {\n");


	indent(level + 1);
	printf("Load Factor: %f\n", ht->load_factor);

	indent(level + 1);
	printf("Primary:\n");
	fhtable_dump(ht->primary, level + 2);

	indent(level + 1);
	printf("Secondary:\n");
	fhtable_dump(ht->secondary, level + 2);

	indent(level + 1);
	printf("Migration Index: %lu\n", ht->migration_idx);

	printf("}\n");
}

/******************************************************************************/

void _adhtable_set_secondary(struct adhtable *ht, const char *key,
			    const char *value)
{
	fhtable_set(ht->secondary, key, value);
	_adhtable_migrate(ht);
}

void _adhtable_set_primary(struct adhtable *ht, const char *key,
			  const char *value)
{
	if (!fhtable_set(ht->primary, key, value)) {
		_adhtable_init_secondary(ht);
		_adhtable_set_secondary(ht, key, value);
	}
}

void _adhtable_init_secondary(struct adhtable *ht)
{
	unsigned long pri_cap = fhtable_capacity(ht->primary);
	unsigned long sec_cap = pri_cap * DHTABLE_GROWTH_FACTOR;

	ht->secondary = fhtable_new(sec_cap, ht->load_factor, ht->hash_func);
}

void _adhtable_migrate(struct adhtable *ht)
{
	unsigned long moved_data = 0;
	do {
		moved_data = fhtable_move(ht->secondary, ht->primary,
					  ht->migration_idx++);
	} while (moved_data == 0);

	if (fhtable_is_empty(ht->primary)) {
		ht->migration_idx = 0;
		fhtable_free(ht->primary);
		ht->primary = ht->secondary;
		ht->secondary = NULL;
	}
}
