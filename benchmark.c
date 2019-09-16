#include "dhtable.h"
#include "hash.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>

#define HASH_ALGORITHM djb2
#define LOAD_FACTOR 0.75
#define INIT_CAPACITY 128
#define REPORT_FILE_SET "report_set.txt"
#define REPORT_FILE_GET "report_get.txt"

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
	FILE *fdata, *fset, *fget;
	struct dhtable *ht;
	char buffer[256];

	if (argc < 2) {
		fprintf(stderr, "Required data file.\n");
		return 1;
	}

	fdata = fopen(argv[1], "r");
	fget = fopen(REPORT_FILE_GET, "w");
	fset = fopen(REPORT_FILE_SET, "w");

	if (!fdata || !fget || !fget) {
		fprintf(stderr, "Cannot open files.\n");
		return 1;
	}

	ht = dhtable_new(INIT_CAPACITY, LOAD_FACTOR, HASH_ALGORITHM);

	while (fscanf(fdata, "%s", buffer) != EOF)
		fprintf(fset, "%lu\n", set(ht, buffer, buffer));

	rewind(fdata);

	while (fscanf(fdata, "%s", buffer) != EOF)
		fprintf(fget, "%lu\n", get(ht, buffer));

	dhtable_free(ht);

	fclose(fdata);
	fclose(fget);
	fclose(fset);

	puts("Done");
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
