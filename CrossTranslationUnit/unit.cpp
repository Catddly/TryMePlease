#include "Declarations.h"

#include <stdio.h>

const int k = 4;

void PrintTranslationUnit()
{
	printf("a = %d,    &a = 0x%p\n", a, &a);
	printf("b = %d,    &b = 0x%p\n", b, &b);
	printf("k = %d,    &k = 0x%p\n", k, &k);
}