#include "fhtable.h"
#include "../formatter/formatter.h"

#include <stdlib.h>
#include <stdio.h>

/* Private APIs */

void _fhtable_add_entry(struct fhtable *ht, struct entry *e);

/******************************************************************************/

struct fhtable *fhtable_new(unsigned long capacity,
			    double load_ratio,
			    unsigned long (*hash_func)(const char*))
{
	struct fhtable *ht = malloc(sizeof(struct fhtable));

	ht->hash_func = hash_func;
	ht->capacity = capacity;
	ht->limit = load_ratio * ht->capacity;
	ht->size = 0;

	ht->slots = malloc(ht->capacity * sizeof(void*));
	for (unsigned long i = 0; i < ht->capacity; ++i)
		ht->slots[i] = list_new();

	return ht;
}

void fhtable_free(struct fhtable *ht)
{
	if (!ht)
		return;

	for (unsigned long i = 0; i < ht->capacity; ++i)
		list_string_entry_free(ht->slots[i]);

	free(ht->slots);
	free(ht);
}

char fhtable_set(struct fhtable *ht,
		 const char *key,
		 const char *value)
{
	if (ht->size >= ht->limit)
		return 0;

	struct entry *e = string_entry_new(key, value);
	_fhtable_add_entry(ht, e);
	return 1;
}

struct string *fhtable_get(const struct fhtable *ht, const char *key)
{
	unsigned long chain_idx = ht->hash_func(key) % ht->capacity;
	struct entry *e = list_string_entry_find(ht->slots[chain_idx], key);

	if (!e)
		return NULL;

	return entry_get_value(e);
}


unsigned long fhtable_capacity(const struct fhtable *ht)
{
	return ht->capacity;
}

unsigned long fhtable_size(const struct fhtable *ht)
{
	return ht->size;
}

char fhtable_dump(const struct fhtable *ht, int level)
{
	formatter_indent(level);
	printf("Fixed Hash Table: {\n");

	formatter_indent(level + 1);
	printf("Limit: %lu\n", ht->limit);

	formatter_indent(level + 1);
	printf("Capacity: %lu\n", ht->capacity);

	formatter_indent(level + 1);
	printf("Size: %lu\n", ht->size);

	formatter_indent(level + 1);
	printf("slots: {\n");

	for (unsigned long i = 0; i < ht->capacity; ++i) {
		formatter_indent(level + 2);
		printf("Index: %lu\n", i);

		list_string_entry_dump(ht->slots[i], level +  2);
	}

	formatter_indent(level + 1);
	printf("}\n");

	formatter_indent(level);
	printf("}\n");
}

/******************************************************************************/

void _fhtable_add_entry(struct fhtable *ht, struct entry *e)
{
	unsigned long chain_idx =
		string_entry_hash(e, ht->hash_func) % ht->capacity;

	list_add(ht->slots[chain_idx], e);

	++ht->size;
}
