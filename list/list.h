#ifndef LIST_H
#define LIST_H

struct node {
	void *data;
	struct node *next;
};

struct list {
	unsigned long size;
	struct node *head;
	struct node *tail;
};

struct list *list_new();
/*
 * Deallocates the list and its data if deallocator is provided.
 */
void list_free(struct list *l, void (*deallocator)(void*));

void list_add(struct list *l, void *data);
/*
 * Deletes a node from the list from its iterator. Deallocates its data if
 * deallocator is provided.
 */
void list_del(struct list *l, struct node *it, void (*deallocator)(void*));
/*
 * Returns size of the list.
 */
unsigned long list_size(const struct list *l);

/*
 * Returns the list's beginning iterator.
 */
struct node *list_begin(const struct list *l);
/*
 * Returns next element. Usage:
 *
 *	struct node *it = list_begin(l);
 *	while ((it = list_next(it))) {
 *		printf("%ld\n", (long) list_iterator_value(it));
 *	}
 */
struct node *list_next(const struct node* n);

/*
 * Returns iterator's value.
 */
void *list_iterator_value(const struct node *n);

#endif
