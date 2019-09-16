#ifndef ADHTABLE_H
#define ADHTABLE_H

/*
 * Advanced Dynamic hash table, built on top of fhtable.
 * With incremental expansion strategy, this one can easily scale up seamlessly
 * as the data grows.
 */

#include "fhtable.h"

struct adhtable {
	unsigned long (*hash_func)(const char*);
	double load_factor;

	struct fhtable *primary;
	struct fhtable *secondary;

	unsigned long migration_idx;
};

/*
 * Creates a new adhtable.
 */
struct adhtable *adhtable_new(unsigned long capacity,
			    double load_factor,
			    unsigned long (*hash_func)(const char*));
/*
 * Free adhtable from memory.
 */
void adhtable_free(struct adhtable *ht);
/*
 * Sets a new key-value pair into adhtable. Migrates data internally if needed.
 */
void adhtable_set(struct adhtable *ht, const char *key, const char *value);
/*
 * Gets the value given a key. Returns NULL if not found. Migrates data
 * internally if needed.
 */
struct string *adhtable_get(struct adhtable *ht, const char *key);
/*
 * Gets the number of records in hash table.
 */
unsigned long adhtable_size(const struct adhtable* ht);
/*
 * Print adhtable to stdout for debugging purpose.
 */
void adhtable_dump(const struct adhtable *ht, unsigned long level);

#endif
