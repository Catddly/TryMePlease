#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Rules to help you do conversion from runtime version to compile-time version.
/// 
/// Rule 1:
/// Change:
/// if (true_condition)
///		return true_expr;
/// else
///		return false_expr;
/// To ->
///		return (true_condition ? true_expr : false_expr);
/// 
/// Rule 2:
/// Change:
/// if (true_condition)
///		return true_expr;
/// else
///		return false;
/// To ->
///		return true_condition && true_expr; // due to short-circuit evaluation, if true_condition is false, then true_expr won't be executed.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned HalfN>
struct is_prime_recursive
{
	static const bool value = (N % HalfN != 0) && is_prime_recursive<N, HalfN - 1>::value;
};

template <unsigned N>
struct is_prime_recursive<N, 2>
{
	static const bool value = (N % 2 != 0);
};

template <unsigned N>
struct is_prime
{
	static const bool value = is_prime_recursive<N, N / 2>::value;
};

template <>
struct is_prime<3>
{
	static const bool value = true;
};

template <>
struct is_prime<2>
{
	static const bool value = true;
};

template <>
struct is_prime<1>
{
	static const bool value = false;
};

template <>
struct is_prime<0>
{
	static const bool value = false;
};

int main()
{
	printf("1 is prime? %s\n",  is_prime<1>::value ? "True" : "False");
	printf("2 is prime? %s\n",  is_prime<2>::value ? "True" : "False");
	printf("3 is prime? %s\n",  is_prime<3>::value ? "True" : "False");
	printf("4 is prime? %s\n",  is_prime<4>::value ? "True" : "False");
	printf("5 is prime? %s\n",  is_prime<5>::value ? "True" : "False");
	printf("6 is prime? %s\n",  is_prime<6>::value ? "True" : "False");
	printf("7 is prime? %s\n",  is_prime<7>::value ? "True" : "False");
	printf("8 is prime? %s\n",  is_prime<8>::value ? "True" : "False");
	printf("9 is prime? %s\n",  is_prime<9>::value ? "True" : "False");
	printf("10 is prime? %s\n", is_prime<10>::value ? "True" : "False");
	printf("11 is prime? %s\n", is_prime<11>::value ? "True" : "False");
	printf("12 is prime? %s\n", is_prime<12>::value ? "True" : "False");
	printf("13 is prime? %s\n", is_prime<13>::value ? "True" : "False");
	printf("14 is prime? %s\n", is_prime<14>::value ? "True" : "False");
	printf("15 is prime? %s\n", is_prime<15>::value ? "True" : "False");
}														 