#ifndef FHTABLE_H
#define FHTABLE_H

#include "../list_string_entry/list_string_entry.h"

/**
 * Simple hash table that could not expand itself.
 */
struct fhtable {
	unsigned long (*hash)(const char*);

	unsigned long limit;
	unsigned long capacity;

	unsigned long size;
	struct list **chains;
};

struct fhtable *fhtable_new(unsigned long capacity,
			    double load_ratio,
			    unsigned long (*hash)(const char*));
void fhtable_free(struct fhtable *ht);

#endif
