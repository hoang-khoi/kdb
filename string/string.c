#include "string.h"
#include <string.h>
#include <stdlib.h>

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

char *string_get_buffer(const struct string *str)
{
	return str->buffer;
}

unsigned long string_length(const struct string *str)
{
	return str->length;
}