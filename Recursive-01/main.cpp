#include <stdio.h>

template <unsigned N>
struct sum // keep recursing
{
	static const unsigned value = N + sum<N - 1>::value;
};

template <>
struct sum<1> // to escape from recursive, the recursive basis
{
	static const unsigned value = 1;
};

int main()
{
	printf("Sum(10)  = %u\n", sum<10>::value);
	printf("Sum(100) = %u\n", sum<100>::value);
}