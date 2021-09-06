#include <stdio.h>
#include <type_traits>

#include <vector>
#include <deque>
#include <set>

/// old ways to do SFINAE check
// primary template
template <typename T1, typename T2, typename = std::void_t<>>
struct modulo_check : public std::false_type
{
};

// template partial specialization
template <typename T1, typename T2>
struct modulo_check<T1, T2, std::void_t<decltype(std::declval<T1>() % std::declval<T2>())>> : public std::true_type
{
};

template <typename T1, typename T2>
constexpr bool can_do_modulo_v = modulo_check<T1, T2>::value;

template <typename T1, typename T2, typename = std::enable_if_t<can_do_modulo_v<T1, T2>>>
auto ModuloSFINAE(T1 a, T2 b)
{
	return a % b;
}

/// new and simple ways to do SFINAE check
// keyword requires and concept are introduced in C++20
template <typename T1, typename T2>
concept CanDoModulo = requires (T1 a, T2 b)
{
	a % b;
};

template <typename T>
concept IntegralType = std::is_integral_v<T>;

template <IntegralType T1, IntegralType T2>
auto ModuloConcept(T1 a, T2 b)
{
	return a % b;
}

template <typename T1, typename T2>
auto ModuloRequires(T1 a, T2 b)
requires requires
{
	a % b;    // can do T1() % T2()
	a.~T1();  // can do T1().~T1()
	a.~T2();  // can do T2().~T2()
}
{
	return a % b;
}

template <typename T1, typename T2>
auto ModuloConstraints(T1 a, T2 b)
requires IntegralType<T1> && IntegralType<T2>
{
	return a % b;
}

//template <template<typename> class Cntr, typename T = int>
//auto PushFrontTest(Cntr<T> a)
//requires requires
//{
//	a.push_front();
//}
//{
//
//}

int main()
{
	printf("8 %% 3 = %d\n", ModuloConcept(8, 3));
	printf("8 %% 3 = %d\n", ModuloRequires(8, 3));
	printf("8 %% 3 = %d\n", ModuloConstraints(8, 3));
	printf("8 %% 3 = %d\n", ModuloSFINAE(8, 3));

	printf("Can do modulo<int, int>?    %s\n", can_do_modulo_v<int, int> ? "True" : "False");
	printf("Can do modulo<double, int>? %s\n", can_do_modulo_v<double, int> ? "True" : "False");

	//printf("8 %% 3 = %d\n", Modulo(8.0, 3)); // [ERROR]! Due to concept, 8.0 is double and it is not accept by compiler.
}