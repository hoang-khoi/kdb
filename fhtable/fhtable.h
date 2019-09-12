#ifndef FHTABLE_H
#define FHTABLE_H

#include "../list_string_entry/list_string_entry.h"

/*
 * Fixed hash table.
 *
 * This is a simple implementation of hash table which resolves conflict by
 * separate chaining strategy.
 *
 * The number of "slots" and load factor are fixed, that means, fhtable has
 * a limited capacity.
 *
 * fhtable is used as corner stones for dhtable (dynamic hash table).
 */

struct fhtable {
	unsigned long (*hash_func)(const char*);

	unsigned long limit;
	unsigned long capacity;

	unsigned long size;
	struct list **slots;
};

/*
 * Creates a new fhtable.
 */
struct fhtable *fhtable_new(unsigned long capacity,
			    double load_ratio,
			    unsigned long (*hash_func)(const char*));
/*
 * Releases fhtable's memory.
 */
void fhtable_free(struct fhtable *ht);
/*
 * Add new entry to the hash table. Return 1 if success, 0 if the table is
 * already full.
 *
 * If 1 is returned, the record has not been added to the hash table.
 */
char fhtable_set(struct fhtable *ht,
		 const char *key,
		 const char *value);
/*
 * Given key, return the associated value, NULL if not found.
 */
struct string *fhtable_get(const struct fhtable *ht, const char *key);
/*
 * Returns fhtable's capacity.
 */
unsigned long fhtable_capacity(const struct fhtable *ht);
/*
 * Returns number of records in fhtable.
 */
unsigned long fhtable_size(const struct fhtable *ht);
/*
 * Checks if fhtable is empty.
 */
char fhtable_is_empty(const struct fhtable *ht);
/*
 * Moves entries of one slot from a hash table to another one.
 * **WARNING: Make sure dest hash table have enough capacity.**
 */
unsigned long fhtable_move(struct fhtable *dest, struct fhtable *src,
			   unsigned long slot_idx);
/*
 * Dumps the hash table to stdout for debugging purpose.
 */
void fhtable_dump(const struct fhtable *ht, unsigned long level);

#endif
