#include <stdio.h>

// primary template
template <typename T>
struct test
{
	using type = T;

	static constexpr void which()
	{
		printf("Primary template called!\n");
	}
};

// specialization template
template <typename T>
struct test<T&>
{
	using type = T&;

	static constexpr void which()
	{
		printf("Specialization template called!\n");
	}
};

void Test()
{
	// we can trace that what template had been called.
	test<int>::which();
	test<int&>::which();
}

int main()
{
	Test();
}