#include <stdio.h>

template <typename T>
struct is_intergel
{
	static const bool valye = false;
};

// template specialization
template <>
struct is_intergel<int>
{
	static const bool value = true;
	using type = int;
};

template <>
struct is_intergel<unsigned>
{
	static const bool value = true;
	using type = unsigned;
};

template <>
struct is_intergel<long long>
{
	static const bool value = true;
	using type = long long;
};

template <>
struct is_intergel<unsigned long long>
{
	static const bool value = true;
	using type = unsigned long long;
};

template <typename T>
constexpr bool is_intergel_v = is_intergel<T>::value;

template <typename T>
using is_intergel_t = typename is_intergel<T>::type;

template <typename T, typename S>
struct is_same
{
	static const bool value = false;
};

template <typename T>
struct is_same<T, T>
{
	static const bool value = true;
	using type = T;
};

template <bool bEnable, typename T = void>
struct enable_if
{
};

// template partial specialization
template <typename T>
struct enable_if<true, T>
{
	using type = T;
};


template <typename T>
struct Printer
{
	void Print(T v)
	{
		printf("%d\n", v);
	}

	//! If type S and type T is not the same, type void will be SFIANE out,
	//! and this function will not exist in runtime.
	template <typename S, typename = typename is_same<T, S>::type>
	void PrintStrict(S v)
	{
		printf("%d\n", v);
	}

	///! Use this way to achieve SFINAE out, to get the fully same effect as above.
	//template <typename S>
	//typename enable_if<is_same<S, T>::value, void>::type
	//PrintStrict(S v)
	//{
	//	printf("%d\n", v);
	//}
};

int main()
{
	Printer<int> printer;
	printer.Print(6);
	printer.Print(45.54); // this will be implicitly cast to int

	printer.PrintStrict(5);
	printer.PrintStrict(48);
	//printer.PrintStrict(48.5); // [ERROR]! 48.5 is double, do not match the type int, so PrintStrict() will be SFINAE out.
}