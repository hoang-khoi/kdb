#include "dhtable.h"
#include "hash.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>

#define HASH_ALGORITHM sdbm
#define LOAD_FACTOR 0.75
#define INIT_CAPACITY 8

/*
 * Simple wrapper over dhtable_set(), but clock_t will be
 * returned to measure the operation's performance.
 */
static unsigned long set(struct dhtable *ht, const char *key,
			 const char *value);
/*
 * Simple wrapper over dhtable_set(), but clock_t will be
 * returned to measure the operation's performance.
 */
static unsigned long get(struct dhtable *ht, const char *key);

/******************************************************************************/

int main(int argc, char **argv)
{
	FILE *fdata;
	struct dhtable *ht;
	char buffer[256];
	unsigned long counter;

	if (argc < 2) {
		fprintf(stderr, "Required data file.\n");
		return 1;
	}

	fdata = fopen(argv[1], "r");

	if (!fdata) {
		fprintf(stderr, "Cannot open file.\n");
		return 1;
	}

	ht = dhtable_new(INIT_CAPACITY, LOAD_FACTOR, HASH_ALGORITHM);
	counter = 0;

	while (fscanf(fdata, "%s", buffer) != EOF) {
		++counter;
		printf("%lu %lu %s\n", counter, set(ht, buffer, buffer), buffer);
	}

	rewind(fdata);
	counter = 0;
	printf("\n");

	while (fscanf(fdata, "%s", buffer) != EOF) {
		++counter;
		printf("%lu %lu %s\n", counter, get(ht, buffer), buffer);
	}

	dhtable_free(ht);
	fclose(fdata);
}

/******************************************************************************/

static unsigned long set(struct dhtable *ht, const char *key,
			 const char *value)
{
	clock_t start = clock();
	dhtable_set(ht, key, value);

	return (unsigned long) clock() - start;
}

static unsigned long get(struct dhtable *ht, const char *key)
{
	clock_t start, stop;
	struct string *value;

	start = clock();
	value = dhtable_get(ht, key);
	stop = clock();

	assert(value);
	assert(string_equals(value, key));

	return (unsigned long) (stop - start);
}
