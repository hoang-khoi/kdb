#ifndef DHTABLE_H
#define DHTABLE_H

#include "../fhtable/fhtable.h"

struct dhtable {
	unsigned long (*hash_func)(const char*);
	double load_factor;

	struct fhtable *primary;
	struct fhtable *secondary;
};

struct dhtable *dhtable_new(unsigned long capacity,
			    double load_factor,
			    unsigned long (*hash_func)(const char*));
void dhtable_free(struct dhtable *ht);

unsigned long dhtable_size(const struct dhtable* ht);

#endif
