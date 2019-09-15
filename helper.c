#include "helper.h"
#include <stdio.h>

void indent(int level)
{
	for (int i = 0; i < level; ++i)
		putchar('\t');
}
