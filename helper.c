#include "helper.h"
#include <stdio.h>

void indent(int level)
{
	int i;
	for (i = 0; i < level; ++i)
		putchar('\t');
}
