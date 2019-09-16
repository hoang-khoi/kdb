#include "adhtable.h"
#include "dhtable.h"
#include "hash.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define HASH_ALGORITHM djb2
#define LOAD_FACTOR 0.75
#define INIT_CAPACITY 128
#define REPORT_FILE_SET "report_set.txt"
#define REPORT_FILE_GET "report_get.txt"

/*
 * Simple wrapper over adhtable_set(), but clock_t will be
 * returned to measure the operation's performance.
 */
static unsigned long clock_adhtable_set(struct adhtable *ht, const char *key,
					const char *value);
/*
 * Simple wrapper over adhtable_set(), but clock_t will be
 * returned to measure the operation's performance.
 */
static unsigned long clock_adhtable_get(struct adhtable *ht, const char *key);
/*
 * dhtable_set() but clock_t will be returned.
 */
static unsigned long clock_dhtable_set(struct dhtable *ht, const char *key,
				       const char *value);
/*
 * dhtable_get(), but the result is checked and clock_t is returned.
 */
static unsigned long clock_dhtable_get(struct dhtable *ht, const char *key);
/*
 * Performs benchmarking adhtable
 */
static void benchmark_adhtable(FILE *fdata, FILE *fset, FILE *fget);
/*
 * Perforams benchmarking dhtable
 */
static void benchmark_dhtable(FILE *fdata, FILE *fset, FILE *fget);

/******************************************************************************/

int main(int argc, char **argv)
{
	FILE *fdata, *fset, *fget;

	if (argc < 3) {
		fprintf(stderr, "Required data structure and data file.\n");
		fprintf(stderr, "Supported data structures:\n");
		fprintf(stderr, "\t* adhtable\n");
		fprintf(stderr, "\t* dhtable\n");

		return 1;
	}

	fdata = fopen(argv[2], "r");
	fget = fopen(REPORT_FILE_GET, "w");
	fset = fopen(REPORT_FILE_SET, "w");

	if (!fdata || !fget || !fget) {
		fprintf(stderr, "Cannot open files.\n");
		return 1;
	}

	if (0 == strcmp(argv[1], "adhtable"))
		benchmark_adhtable(fdata, fset, fget);
	else if (0 == strcmp(argv[1], "dhtable"))
		benchmark_dhtable(fdata, fset, fget);
	else
		puts("Unsupported data structure");

	fclose(fdata);
	fclose(fget);
	fclose(fset);

	puts("Done");

	return 0;
}

/******************************************************************************/

static void benchmark_adhtable(FILE *fdata, FILE *fset, FILE *fget)
{
	char buffer[256];
	struct adhtable *ht;

	ht = adhtable_new(INIT_CAPACITY, LOAD_FACTOR, HASH_ALGORITHM);

	while (fscanf(fdata, "%s", buffer) != EOF)
		fprintf(fset, "%lu\n", clock_adhtable_set(ht, buffer, buffer));

	rewind(fdata);

	while (fscanf(fdata, "%s", buffer) != EOF)
		fprintf(fget, "%lu\n", clock_adhtable_get(ht, buffer));

	adhtable_free(ht);
}

static void benchmark_dhtable(FILE *fdata, FILE *fset, FILE *fget)
{
	char buffer[256];
	struct dhtable *ht;

	ht = dhtable_new(INIT_CAPACITY, LOAD_FACTOR, HASH_ALGORITHM);

	while (fscanf(fdata, "%s", buffer) != EOF)
		fprintf(fset, "%lu\n", clock_dhtable_set(ht, buffer, buffer));

	rewind(fdata);

	while (fscanf(fdata, "%s", buffer) != EOF)
		fprintf(fget, "%lu\n", clock_dhtable_get(ht, buffer));

	dhtable_free(ht);
}

static unsigned long clock_adhtable_get(struct adhtable *ht, const char *key)
{
	clock_t start, stop;
	struct string *value;

	start = clock();
	value = adhtable_get(ht, key);
	stop = clock();

	assert(value);
	assert(string_equals(value, key));

	return (unsigned long) (stop - start);
}

static unsigned long clock_adhtable_set(struct adhtable *ht, const char *key,
				        const char *value)
{
	clock_t start = clock();
	adhtable_set(ht, key, value);

	return (unsigned long) clock() - start;
}

static unsigned long clock_dhtable_get(struct dhtable *ht, const char *key)
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

static unsigned long clock_dhtable_set(struct dhtable *ht, const char *key,
				       const char *value)
{
	clock_t start = clock();
	dhtable_set(ht, key, value);

	return (unsigned long) clock() - start;
}
