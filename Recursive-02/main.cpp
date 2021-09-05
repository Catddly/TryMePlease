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

/// begin
/// Step 1: Write a runtime algorithm.
/// runtime algorithm in one function
/// it may not be the most efficient one, but it is a good example
bool RT_is_prime(unsigned n)
{
	if (n < 4) // n = 0, 1, 2, 3
		return n > 1; // n = 0 or 1, it is false
	else
	{
		unsigned halfN = n / 2;
		for (int i = halfN; i >= 2; --i)
		{
			if (n % i == 0)
				return false;
		}
	}
	return true;
}

/// Step 2: Use the rules above to convert the algorithm to recursive format.
/// it will be ->
/// ( n < 4 ) ? ( n > 1 ) : ( false_expr ); { Rule 1 }
/// and false_expr will be ( notice that there is a for loop ) ->
/// [Recursive] (n % i != 0 && is_prime_recursive<n, halfN - 1>::value) { Rule 2 }
/// [Recursive Basis] when halfN == 2 -> ( n % i != 0 )

/// Step 3: convert it to TMP format.

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

/// end

void PrintRT()
{
	printf("1  is prime? %s\n", RT_is_prime(1) ? "True" : "False");
	printf("2  is prime? %s\n", RT_is_prime(2) ? "True" : "False");
	printf("3  is prime? %s\n", RT_is_prime(3) ? "True" : "False");
	printf("4  is prime? %s\n", RT_is_prime(4) ? "True" : "False");
	printf("5  is prime? %s\n", RT_is_prime(5) ? "True" : "False");
	printf("6  is prime? %s\n", RT_is_prime(6) ? "True" : "False");
	printf("7  is prime? %s\n", RT_is_prime(7) ? "True" : "False");
	printf("8  is prime? %s\n", RT_is_prime(8) ? "True" : "False");
	printf("9  is prime? %s\n", RT_is_prime(9) ? "True" : "False");
	printf("10 is prime? %s\n", RT_is_prime(10) ? "True" : "False");
	printf("11 is prime? %s\n", RT_is_prime(11) ? "True" : "False");
	printf("12 is prime? %s\n", RT_is_prime(12) ? "True" : "False");
	printf("13 is prime? %s\n", RT_is_prime(13) ? "True" : "False");
	printf("14 is prime? %s\n", RT_is_prime(14) ? "True" : "False");
	printf("15 is prime? %s\n", RT_is_prime(15) ? "True" : "False");
}

void PrintCT()
{
	printf("1  is prime? %s\n", is_prime<1>::value ? "True" : "False");
	printf("2  is prime? %s\n", is_prime<2>::value ? "True" : "False");
	printf("3  is prime? %s\n", is_prime<3>::value ? "True" : "False");
	printf("4  is prime? %s\n", is_prime<4>::value ? "True" : "False");
	printf("5  is prime? %s\n", is_prime<5>::value ? "True" : "False");
	printf("6  is prime? %s\n", is_prime<6>::value ? "True" : "False");
	printf("7  is prime? %s\n", is_prime<7>::value ? "True" : "False");
	printf("8  is prime? %s\n", is_prime<8>::value ? "True" : "False");
	printf("9  is prime? %s\n", is_prime<9>::value ? "True" : "False");
	printf("10 is prime? %s\n", is_prime<10>::value ? "True" : "False");
	printf("11 is prime? %s\n", is_prime<11>::value ? "True" : "False");
	printf("12 is prime? %s\n", is_prime<12>::value ? "True" : "False");
	printf("13 is prime? %s\n", is_prime<13>::value ? "True" : "False");
	printf("14 is prime? %s\n", is_prime<14>::value ? "True" : "False");
	printf("15 is prime? %s\n", is_prime<15>::value ? "True" : "False");
}

int main()
{
	PrintRT();
	printf("\n");
	PrintCT();
}														 