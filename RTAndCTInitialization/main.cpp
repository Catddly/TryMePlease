#include <stdio.h>

          const int RT_GetValue() { return 4; }
constexpr const int CT_GetValue() { return 4; }

// at runtime
void RT_Initialization()
{
	const int b = RT_GetValue();
	int* p = (int*)&b;  // this will force compiler to allocate memory for b
	*p = 0;

	printf("--------------RT_Initialization\n");
	printf("b         = %d,   &b = 0x%p\n", b, &b);
	printf("*(&b)     = %d,   &b = 0x%p\n", *(&b), &b);
	printf("*(int*)&b = %d,   &b = 0x%p\n", *(int*)&b, (int*)&b);
	printf("*p        = %d,    p = 0x%p\n", *p, p);
}

// at compile-time
void CT_Initialization()
{
	constexpr int b = CT_GetValue();
	int* p = (int*)&b; // this will force compiler to allocate memory for b
	*p = 0;

	printf("--------------CT_Initialization\n");
	printf("b         = %d,   &b = 0x%p\n", b, &b);
	printf("*(&b)     = %d,   &b = 0x%p\n", *(&b), &b);
	printf("*(int*)&b = %d,   &b = 0x%p\n", *(int*)&b, (int*)&b);
	printf("*p        = %d,    p = 0x%p\n", *p, p);
}

int main()
{
	CT_Initialization();
	RT_Initialization();
}