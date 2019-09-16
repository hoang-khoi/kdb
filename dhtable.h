#ifndef DHTABLE_H
#define DHTABLE_H

#include "fhtable.h"

/*
 * Simple implementation of a dynamic hash table. When it is full, the table
 * simply expands itself and rehash all of its records.
 */

struct dhtable {
	struct fhtable *primary;
	double load_factor;
	unsigned long (*hash_func)(const char*);
};

/*
 * Creates a new dhtable.
 */
struct dhtable *dhtable_new(unsigned long capacity, double load_factor,
			    unsigned long (*hash_func)(const char*));
/*
 * Free the table.
 */
void dhtable_free(struct dhtable *ht);
/*
 * Sets a new key-value into the table. Expands and rehashes itself if
 * necessary.
 */
void dhtable_set(struct dhtable *ht, const char *key, const char *value);
/*
 * Gets the value associated with a key. Returns NULL if not found.
 */
struct string *dhtable_get(struct dhtable *ht,  const char *key);
/*
 * Returns number of records in the table.
 */
unsigned long dhtable_size(const struct dhtable *ht);
/*
 * Returns current capacity of hash table.
 */
unsigned long dhtable_capacity(const struct dhtable *ht);
/*
 * Prints a dhtable to stdout for debugging purpose.
 */
void dhtable_dump(const struct dhtable *ht, unsigned long level);

#endif
