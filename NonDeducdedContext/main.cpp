#include <stdio.h>
#include <type_traits>

// In this case, the type of T is deducible
template <typename T>
void SimpleDeduction(T a)
{

}

/// primary template
template <typename T>
struct MyType
{
	using type = T;
};

/// specialization template [int]
template <>
struct MyType<int>
{
	using type = int;
};

/// specialization template [double]
template <>
struct MyType<double>
{
	using type = int;
};

// Here, the type of Mytype<>::type is non-deducible context.
// Due to the nest structure of MyType<T>::type, this is a non-deducible context.
template <typename T>
void NonDeducedContext( typename MyType<T>::type t )
{

}

// Here we see there is a nest structure in std::remove_reference<T>.
template <typename T>
T&& forward(std::remove_reference_t<T> args)
{
	return static_cast<T&&>(args);
}

// No nest structure in function parameters.
template <typename T>
std::remove_reference_t<T>&& move(T&& arg)
{
	return static_cast<std::remove_reference_t<T>&&>(arg);
}

int main()
{
	int a = 6;

	SimpleDeduction(a);
	// NonDeducedContext(a); // [ERROR]! 'void NonDeducedContext(MyType<T>::type)': could not deduce template argument for 'T'.

	forward<int>(a); // Non-deducible context. Should give the template parameter explicitly.
	move(a);         // Type of a is deducible!
}