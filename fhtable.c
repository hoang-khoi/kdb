#include "fhtable.h"
#include "helper.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Add a new key-value entry into fhtable.
 * NOTE: Any new data adding operations MUST be done by this function.
 */
void _fhtable_add_entry(struct fhtable *ht, struct entry *e);

/******************************************************************************/

struct fhtable *fhtable_new(unsigned long capacity,
			    double load_factor,
			    unsigned long (*hash_func)(const char*))
{
	struct fhtable *ht = malloc(sizeof(struct fhtable));
	unsigned long i;

	ht->hash_func = hash_func;
	ht->capacity = capacity;
	ht->limit = load_factor * ht->capacity;
	ht->size = 0;

	ht->slots = malloc(ht->capacity * sizeof(void*));
	for (i = 0; i < ht->capacity; ++i)
		ht->slots[i] = list_new();

	return ht;
}

void fhtable_free(struct fhtable *ht)
{
	unsigned long i;

	if (!ht)
		return;

	for (i = 0; i < ht->capacity; ++i)
		list_string_entry_free(ht->slots[i]);

	free(ht->slots);
	free(ht);
}

char fhtable_set(struct fhtable *ht,
		 const char *key,
		 const char *value)
{
	struct entry *e;

	if (ht->size >= ht->limit)
		return 0;

	e = string_entry_new(key, value);
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

char fhtable_is_empty(const struct fhtable *ht)
{
	return ht->size == 0;
}

unsigned long fhtable_move(struct fhtable *dest, struct fhtable *src,
			   unsigned long slot_idx)
{
	unsigned long entries_moved = 0;
	struct list *slot_to_move = src->slots[slot_idx];
	struct node *iterator = list_begin(slot_to_move);

	while (list_next(iterator)) {
		struct entry *e = list_iterator_value(iterator);
		_fhtable_add_entry(dest, e);
		list_del(slot_to_move, iterator, NULL);
		++entries_moved;
	}

	src->size -= entries_moved;

	return entries_moved;
}

void fhtable_dump(const struct fhtable *ht, unsigned long level)
{
	unsigned long i;

	if (!ht) {
		indent(level);
		printf("NULL\n");

		return;
	}

	indent(level);
	printf("Fixed Hash Table: {\n");

	indent(level + 1);
	printf("Limit: %lu\n", ht->limit);

	indent(level + 1);
	printf("Capacity: %lu\n", ht->capacity);

	indent(level + 1);
	printf("Size: %lu\n", ht->size);

	indent(level + 1);
	printf("slots: {\n");

	for (i = 0; i < ht->capacity; ++i) {
		indent(level + 2);
		printf("Index: %lu\n", i);

		list_string_entry_dump(ht->slots[i], level +  2);
	}

	indent(level + 1);
	printf("}\n");

	indent(level);
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
