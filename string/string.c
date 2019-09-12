#include "string.h"
#include "../formatter/formatter.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct string *string_new(const char *buffer)
{
	struct string *s = malloc(sizeof(struct string));
	s->length = strlen(buffer);
	s->buffer = malloc(s->length + 1);
	strcpy(s->buffer, buffer);

	return s;
}

void string_free(struct string *str)
{
	if (!str)
		return;

	free(str->buffer);
	free(str);
}

unsigned long string_length(const struct string *str)
{
	return str->length;
}

int string_equals(const struct string *s, const char *buffer)
{
	return 0 == strcmp(buffer, s->buffer);
}

unsigned long string_hash(const struct string *s,
			  unsigned long (*hash_func)(const char*))
{
	return hash_func(s->buffer);
}

void string_dump(const struct string *s, int level)
{
	formatter_indent(level);
	printf("String: {Length: %lu, Content: '%s'}\n", s->length, s->buffer);
}
