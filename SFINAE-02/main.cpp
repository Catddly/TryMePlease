#include <stdio.h>
#include <type_traits> // std::true_type and std::false_type

// compile-time type T encapsulation.
template <typename T>
struct BoxedType {};

// compile-time type T instance.
template <typename T>
constexpr auto BoxedInstace = BoxedType<T>{};

// function that only have declaration.
//! To fetch type T from BoxedType<T>.
template <typename T>
constexpr T StripBoxedType(BoxedType<T>);

//! Generic lambda.
//! Used to SFINAE out.
template <typename LambdaFunc, typename... Args, typename = decltype(std::declval<LambdaFunc>()(std::declval<Args&&>()...))> // try to call LambdaFunc(Args... args)
std::true_type is_implemented(void*); // accept any pointer

template <typename LambdaFunc, typename... Args>
std::false_type is_implemented(...); // this function can have any parameters

//template <typename Func>
//constexpr auto IsValid(Func&& lambda_instance)
//{
//	return [](auto&&... args)
//	{
//		return decltype(is_implemented<Func, decltype(args)&&...>(nullptr)){};
//	};
//}

// try to call is_implemented(void*) first, if failed, fallback to is_implemented(...)
// this will return true_type or false_type depend on if is_implemented() is SFINAE out
constexpr auto func_is_valid = [](auto lambda_instance)
{
	return [](auto&&... args)
	{
		// we want to return a true_type.
		return decltype(is_implemented<decltype(lambda_instance), decltype(args)&&...>(nullptr)){};
	};
};

// use this function to test what we want, in this case we test if type T can call T()
// if this failed, type Func in IsValid() will be SFINAE out.
constexpr auto func_is_default_constructible = [](auto boxed_instance) -> decltype(decltype( StripBoxedType(boxed_instance) )() /* here we call the default constructor to test */)
{};

constexpr auto func_can_accept_int = [](auto boxed_instance) -> decltype(decltype(StripBoxedType(boxed_instance))(4))
{};

// combine the test function with SFINAE function.
constexpr auto is_default_constructible    = func_is_valid(func_is_default_constructible);
constexpr auto can_accept_int_to_construct = func_is_valid(func_can_accept_int);

struct A
{
	A() = default;
};

struct B
{
	B() = delete;
	B(int b) {}
};

int main()
{
	printf("Is [int]    default constructible? %s\n", is_default_constructible(BoxedInstace<int>) ? "True" : "False");
	printf("Is [int&]   default constructible? %s\n", is_default_constructible(BoxedInstace<int&>) ? "True" : "False");
	printf("Is [double] default constructible? %s\n", is_default_constructible(BoxedInstace<double>) ? "True" : "False");
	printf("Is [A]      default constructible? %s\n", is_default_constructible(BoxedInstace<A>) ? "True" : "False");
	printf("Is [B]      default constructible? %s\n", is_default_constructible(BoxedInstace<B>) ? "True" : "False");
	printf("\n");

	printf("Is [int]    can accept int? %s\n", can_accept_int_to_construct(BoxedInstace<int>) ? "True" : "False");
	printf("Is [int&]   can accept int? %s\n", can_accept_int_to_construct(BoxedInstace<int&>) ? "True" : "False");
	printf("Is [char]   can accept int? %s\n", can_accept_int_to_construct(BoxedInstace<char>) ? "True" : "False");
	printf("Is [double] can accept int? %s\n", can_accept_int_to_construct(BoxedInstace<double>) ? "True" : "False");
	printf("Is [A]      can accept int? %s\n", can_accept_int_to_construct(BoxedInstace<A>) ? "True" : "False");
	printf("Is [B]      can accept int? %s\n", can_accept_int_to_construct(BoxedInstace<B>) ? "True" : "False");
	printf("\n");
}