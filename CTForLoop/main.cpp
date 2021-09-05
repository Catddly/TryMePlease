#include <stdio.h>
#include <utility> // std::forward

// compile-time for loop [I, LIMIT)
template <unsigned I, unsigned LIMIT, typename Func>
constexpr void for_loop(Func&& func)
{
	func(I);

	if constexpr (I + 1 < LIMIT)
		for_loop<I + 1, LIMIT>(std::forward<Func>(func));
};

template <unsigned Start, unsigned End, typename Opr, typename... Types>
constexpr void for_loop(Opr&& operation, Types&&... args)
{
	if constexpr (Start < End)
		operation(std::forward<Types>(args)...);

	if constexpr (Start < End)
		for_loop<Start + 1, End>(std::forward<Opr>(operation), std::forward<Types>(args)...);
}

// for-loop is recursive invoke.
constexpr int factorial(int n)
{
	return n <= 1 ? 1 : n * factorial(n - 1);
}

int main()
{
	for_loop<0, 10>([](unsigned i) { printf("%u\n", i + 5); });
	printf("\n");

	for_loop<0, 10>([](unsigned a, unsigned b) { printf("%u\n", a + b); }, 7, 9);
	printf("\n");

	printf("%d\n", factorial(10));
}