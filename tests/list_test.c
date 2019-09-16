#include "../list.c"
#include <assert.h>

void test_add()
{
	struct list *l = list_new();
	struct node *it;
	void *data[3];
	unsigned long i;

	for (i = 0; i < 3; ++i) {
		data[i] = malloc(16);
		list_add(l, data[i]);
	}

	assert(3 == list_size(l));

	it = list_begin(l);

	for (i = 0; i < list_size(l); ++i) {
		assert(data[i] == list_iterator_value(it));
		it = list_next(it);
	}

	list_free(l, free);

}

void test_del()
{
	struct list *l = list_new();
	void *data[3], *data_2[3];
	struct node *begin, *end, *it;
	unsigned long i;

	for (i = 0; i < 3; ++i) {
		data[i] = malloc(16);
		list_add(l, data[i]);
	}

	begin = list_begin(l);
	end = list_iterator_jump(begin, 2);

	list_del(l, begin, free);
	list_del(l, end, free);

	for (i = 0; i < 3; ++i) {
		data_2[i] = malloc(16);
		list_add(l, data_2[i]);
	}

	assert(4 == list_size(l));

	it = list_begin(l);
	for (i = 0; i < list_size(l); ++i) {
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

	return 0;
}
