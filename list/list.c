#include "list.h"
#include <stdlib.h>

/* NODE PROTOTYPES */

/*
 * Creates a new node.
 */
struct node *node_new(void *data);
/*
 * Deallocates a node and its data if deallocator is provided.
 */
void node_free(struct node *n, void (*deallocator)(void*));

/* LIST IMPLEMENTATION */

struct list *list_new()
{
	struct list *l = malloc(sizeof(struct list));

	l->size = 0;
	l->head = node_new(NULL);
	l->tail = l->head;

	return l;
}

void list_free(struct list *l, void (*deallocator)(void*))
{
	struct node *it = l->head;
	struct node *tmp;

	while (it) {
		tmp = it;
		it = it->next;
		node_free(tmp, deallocator);
	}

	free(l);
}

void list_add(struct list *l, void *data)
{
	l->tail->next = node_new(data);
	l->tail = l->tail->next;
	++l->size;
}

void list_del(struct list *l, struct node *it, void (*deallocator)(void*))
{
	struct node *target = it->next;

	if (it->next == l->tail)
		l->tail = it;

	it->next = it->next->next;
	node_free(target, deallocator);

	--l->size;
}

unsigned long list_size(const struct list *l)
{
	return l->size;
}

struct node *list_begin(const struct list *l)
{
	return l->head;
}

struct node *list_next(const struct node* n)
{
	return n->next;
}

void *list_iterator_value(const struct node *n)
{
	return n->next->data;
}

struct node *list_iterator_jump(struct node *it, unsigned long steps)
{
	for (int i = 0; i < steps; ++i)
		it = list_next(it);

	return it;
}

/* NODE  IMPLEMENTATION */

struct node *node_new(void *data)
{
	struct node *n = malloc(sizeof(struct node));
	n->data = data;
	n->next = NULL;

	return n;
}

void node_free(struct node *n, void (*deallocator)(void*))
{
	if (!n)
		return;

	if (deallocator)
		deallocator(n->data);
	free(n);
}
