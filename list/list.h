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
 * NOTE: The iterator is MOVED forward one node as the specified node has been
 * removed.
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
 * Given the list's iterator, returns its value.
 */
void *list_iterator_value(const struct node *n);

/*
 * Iterates a certain amount of steps, then returns that iterator.
 */
struct node *list_iterator_jump(struct node *it, unsigned long step);

#endif
