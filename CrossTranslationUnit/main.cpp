#include "Declarations.h"

#include <stdio.h>

void PrintMain()
{
	printf("a = %d,    &a = 0x%p\n", a, &a);
	printf("b = %d,    &b = 0x%p\n", b, &b);
	printf("k = %d,    &k = 0x%p\n", k, &k);
}

int main()
{
	PrintTranslationUnit();
	printf("\n");
	PrintMain();
}