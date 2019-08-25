#include "list.c"
#include <assert.h>

/*
 * Helper function for quickly moving the list iterator.
 */
struct node *move_iterator(struct node *it, int steps)
{
	for (int i = 0; i < steps; ++i)
		it = list_next(it);

	return it;
}

void test_add()
{
	struct list *l = list_new();
	void *data[3];

	for (int i = 0; i < 3; ++i) {
		data[i] = malloc(16);
		list_add(l, data[i]);
	}

	// Test list's size
	assert(3 == list_size(l));

	// Testing its elements
	struct node *it = list_begin(l);

	for (int i = 0; i < list_size(l); ++i) {
		assert(data[i] == list_iterator_value(it));
		it = list_next(it);
	}

	list_free(l, free);

}

void test_del()
{
	struct list *l = list_new();
	void *data[3];

	for (int i = 0; i < 3; ++i) {
		data[i] = malloc(16);
		list_add(l, data[i]);
	}

	// Delete first and last
	struct node *begin = list_begin(l);
	struct node *end = move_iterator(begin, 2);

	list_del(l, begin, free);
	list_del(l, end, free);

	// Add something after deletion
	void *data_2[3];
	for (int i = 0; i < 3; ++i) {
		data_2[i] = malloc(16);
		list_add(l, data_2[i]);
	}

	// Test list's size
	assert(4 == list_size(l));

	// Test content
	struct node *it = list_begin(l);
	for (int i = 0; i < list_size(l); ++i) {
		if (i == 0)
			assert(data[1] == list_iterator_value(it));
		else
			assert(data_2[i - 1] == list_iterator_value(it));

		it = list_next(it);
	}

	list_free(l, free);
}

int main()
{
	test_add();
	test_del();
}
