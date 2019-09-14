#include "dhtable.h"
#include "hash.h"

#include <stdio.h>

#define HASH_ALGORITHM sdbm
#define LOAD_FACTOR 0.75
#define INIT_CAPACITY 8

int main()
{
	struct dhtable *ht = dhtable_new(INIT_CAPACITY, LOAD_FACTOR,
					 HASH_ALGORITHM);
	dhtable_free(ht);
	puts("Success");
}
