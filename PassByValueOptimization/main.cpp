#include <stdio.h>
#include <type_traits>

template <typename T>
constexpr bool is_const_reference_v = std::is_reference_v<T> && std::is_const_v<std::remove_reference_t<T>>;

//! Sum from [a, b].
template <typename T>
auto sum(T a, T b)
{
	if constexpr (std::is_pointer_v<T>) // call by pointer
	{
		printf("T is pointer type!\n");
		int s = *a;
		int t = *b;
		decltype(s) sum{};
		for (int i = s; i <= t; ++i)
			sum += i;
		return sum;
	}
	else // neither a nor b is pointer
	{
		if constexpr (std::is_reference_v<T>) // pass by reference
		{
			if constexpr (std::is_lvalue_reference_v<T>)
			{
				if constexpr (is_const_reference_v<T>)
				{
					printf("T is const lvalue reference type!\n");
				}
				else
				{
					printf("T is non-const lvalue reference type!\n");
				}
			}
			else
			{
				printf("T is rvalue reference type!\n");
			}
		}
		else // a and b are neither reference nor pointer, pass by value
		{
			printf("T is simple value type!\n");
		}

		// decltype(a+b) is a compile-time expression (or called const expression)
		auto sum = decltype(a + b){};
		for (int i = a; i <= b; ++i)
			sum += i;
		return sum;
	}
}

int main()
{
	int a = 1, b = 10, c = 100;

	printf("sum(a, b)                              = %d\n", sum(a, b));
	printf("sum(&a, &b)                            = %d\n", sum(&a, &b));
	printf("sum<int&>(a, b)                        = %d\n", sum<int&>(a, b));
	printf("sum<const int&>(a, b)                  = %d\n", sum<const int&>(a, b));
	printf("sum<int&&>(1, 10)                      = %d\n", sum<int&&>(1, 10));
	printf("sum<int&&>(std::move(a), std::move(b)) = %d\n", sum<int&&>(std::move(a), std::move(b)));
	printf("sum<int&&>(1, std::move(c))            = %d\n", sum<int&&>(1, std::move(c)));
}