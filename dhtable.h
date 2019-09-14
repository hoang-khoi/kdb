#ifndef DHTABLE_H
#define DHTABLE_H

/*
 * Dynamic hash table, built on top of fhtable. This one can easily scale up
 * seamlessly as the data grows.
 */

#include "fhtable.h"

struct dhtable {
	unsigned long (*hash_func)(const char*);
	double load_factor;

	struct fhtable *primary;
	struct fhtable *secondary;

	unsigned long migration_idx;
};

/*
 * Creates a new dhtable.
 */
struct dhtable *dhtable_new(unsigned long capacity,
			    double load_factor,
			    unsigned long (*hash_func)(const char*));
/*
 * Free dhtable from memory.
 */
void dhtable_free(struct dhtable *ht);
/*
 * Sets a new key-value pair into dhtable. Migrates data internally if needed.
 */
void dhtable_set(struct dhtable *ht, const char *key, const char *value);
/*
 * Gets the value given a key. Returns NULL if not found. Migrates data
 * internally if needed.
 */
struct string *dhtable_get(struct dhtable *ht, const char *key);
/*
 * Gets the number of records in hash table.
 */
unsigned long dhtable_size(const struct dhtable* ht);

#endif
