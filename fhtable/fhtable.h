#ifndef FHTABLE_H
#define FHTABLE_H

#include "../list_string_entry/list_string_entry.h"

/**
 * Simple hash table that could not expand itself.
 */
struct fhtable {
	unsigned long (*hash_func)(const char*);

	unsigned long limit;
	unsigned long capacity;

	unsigned long size;
	struct list **chains;
};

struct fhtable *fhtable_new(unsigned long capacity,
			    double load_ratio,
			    unsigned long (*hash_func)(const char*));
void fhtable_free(struct fhtable *ht);

/*
 * Add new entry to the hash table. Return 1 if success, 0 if the table is
 * already full.
 */
char fhtable_set(struct fhtable *ht,
		 const char *key,
		 const char *value);
/*
 * Given key, return the associated value, NULL if not found.
 */
struct string *fhtable_get(const struct fhtable *ht, const char *key);

/*
 * Dumps the hash table to stdout for debugging purpose.
 */
char fhtable_dump(const struct fhtable *ht, int level);

#endif
