#include <stdio.h>
#include <string>
#include <type_traits>

template <typename T>
std::string TypeToString()
{
#if defined(_MSC_VER)
	std::string fullName(__FUNCSIG__);
	size_t leftAngleBracket = fullName.find_last_of('<');
	size_t rightAngleBracket = fullName.find_last_of('>');
	std::string name = fullName.substr(leftAngleBracket + 1, rightAngleBracket - leftAngleBracket - 1);
	if (name.find("struct") != std::string::npos)
		return std::move(name.substr(7, name.size() - 7));
	else if (name.find("class") != std::string::npos)
		return std::move(name.substr(6, name.size() - 6));
	else
		return std::move(name);
#endif
}

// type alias
using A = int&;
using C = int&&;
using D = int;
using B = const A;

template <typename T>
struct add_const
{
	using type = const T;
};

template <typename T>
struct add_const<T&>
{
	using type = const T&;
};

template <typename T>
struct add_const<T&&>
{
	using type = const T&&;
};

template <typename T>
using add_const_t = typename add_const<T>::type;

int main()
{
	printf("typename = %s\n", TypeToString<B>().c_str()); // the result is int&, not const int&. 

	printf("typename = %s\n", TypeToString<add_const_t<D>>().c_str());
	printf("typename = %s\n", TypeToString<add_const_t<A>>().c_str());
	printf("typename = %s\n", TypeToString<add_const_t<C>>().c_str());
}