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
char fhtable_add(struct fhtable * ht,
		 const char *key,
		 const char *value);

#endif
