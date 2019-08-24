#ifndef FHTABLE_H
#define FHTABLE_H

#include "../list/list.h"

/**
 * Simple hash table that could not expand itself.
 */
struct fhtable {
	unsigned long (*hash)(const char*);
	unsigned long capacity;
	unsigned long size;
	struct list **chains;
};

struct fhtable_new(double load_ratio, unsigned long (*hash)(const char*));
struct fhtable_free(struct fhtable *ht);

#endif
