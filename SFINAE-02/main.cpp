#include <stdio.h>
#include <type_traits> // std::true_type and std::false_type

#include <vector>
#include <deque>
#include <set>

// compile-time type T encapsulation.
template <typename T>
struct BoxedType {};

// compile-time type T instance.
template <typename T>
constexpr auto BoxedInstance = BoxedType<T>{};

// function that only have declaration.
//! To fetch type T from BoxedType<T>.
//! This return an instance of T.
template <typename T>
constexpr T StripBoxedType(BoxedType<T>);

template <typename T>
constexpr auto ElementInstance(BoxedType<T>) -> decltype(std::declval<typename T::value_type>());

//! Generic lambda.
//! Used to SFINAE out.
template <typename LambdaFunc, typename... Args, typename = decltype(std::declval<LambdaFunc>()(std::declval<Args&&>()...))> // try to call LambdaFunc(Args... args)
std::true_type  is_implemented(void*); // accept any pointer

template <typename LambdaFunc, typename... Args>
std::false_type is_implemented(...);   // this function can have any parameters

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
constexpr auto func_is_valid = [](auto lambda_instance) // lambda_instance is function body
{
	return [](auto&&... args) // args are the parameters of lambda_instance
	{
		// we want to return a true_type.
		// we pass in the nullptr to let the compilers to try is_implemented(void*) first due to
		// the Optimal Selection Principle, if is_implemented(void*) be SFINAE out,
		// then the compiler will try is_implemented(...)
		return decltype(is_implemented<decltype(lambda_instance), decltype(args)&&...>(nullptr)){};
	};
};

// use this function to test what we want, in this case we test if type T can call T()
// if this failed, type Func in IsValid() will be SFINAE out.
// decltype( StripBoxedType(boxed_instance) )() equals to T()
// we want to call T()
constexpr auto func_is_default_constructible = [](auto boxed_instance) -> 
	decltype( decltype( StripBoxedType(boxed_instance) )() ) /* here we call the default constructor to test */
{};

// decltype( StripBoxedType(boxed_instance) )(4) equals to T(4)
// we want to call T(4)
constexpr auto func_can_accept_int = [](auto boxed_instance) -> 
	decltype( decltype( StripBoxedType(boxed_instance) )(4) )
{};

// we want to call T().push_front(value_type instance)
constexpr auto func_can_push_front = [](auto boxed_instance) ->
	decltype( StripBoxedType(boxed_instance).push_front(ElementInstance(boxed_instance)) )
{};

// we want to call T().~T()
constexpr auto func_is_defalut_destructible = [](auto boxed_instance) ->
	decltype(StripBoxedType(boxed_instance).~decltype(StripBoxedType(boxed_instance))() )
{};

// combine the test function with SFINAE function.
constexpr auto is_default_constructible    = func_is_valid(func_is_default_constructible);
constexpr auto is_defalut_destructible     = func_is_valid(func_is_defalut_destructible);
constexpr auto can_accept_int_to_construct = func_is_valid(func_can_accept_int);
constexpr auto have_push_front             = func_is_valid(func_can_push_front);

template <typename T>
constexpr bool is_default_constructible_v    = is_default_constructible(BoxedInstance<T>);
template <typename T>
constexpr bool is_defalut_destructible_v     = is_defalut_destructible(BoxedInstance<T>);
template <typename T>
constexpr bool can_accept_int_to_construct_v = can_accept_int_to_construct(BoxedInstance<T>);

// (template<typename> class Container) refers to std::vector<> or other container type.
template <template<typename> class Container, typename T = int>
constexpr bool have_push_front_v = have_push_front(BoxedInstance<Container<T>>);

struct A
{
	A() = default;
protected:
	~A() = default;
};

struct B
{
	B() = delete;
	B(int b) {}
};

int main()
{
	printf("Is [int]    default constructible? %s\n", is_default_constructible_v<int> ? "True" : "False");
	printf("Is [int&]   default constructible? %s\n", is_default_constructible_v<int&> ? "True" : "False");
	printf("Is [double] default constructible? %s\n", is_default_constructible_v<double> ? "True" : "False");
	printf("Is [A]      default constructible? %s\n", is_default_constructible_v<A> ? "True" : "False");
	printf("Is [B]      default constructible? %s\n", is_default_constructible_v<B> ? "True" : "False");
	printf("\n");

	printf("Is [int]    can accept int? %s\n", can_accept_int_to_construct_v<int> ? "True" : "False");
	printf("Is [int&]   can accept int? %s\n", can_accept_int_to_construct_v<int&> ? "True" : "False");
	printf("Is [char]   can accept int? %s\n", can_accept_int_to_construct_v<char> ? "True" : "False");
	printf("Is [double] can accept int? %s\n", can_accept_int_to_construct_v<double> ? "True" : "False");
	printf("Is [A]      can accept int? %s\n", can_accept_int_to_construct_v<A> ? "True" : "False");
	printf("Is [B]      can accept int? %s\n", can_accept_int_to_construct_v<B> ? "True" : "False");
	printf("\n");

	printf("Is [int]    default destructible? %s\n", is_defalut_destructible_v<int> ? "True" : "False");
	printf("Is [int&]   default destructible? %s\n", is_defalut_destructible_v<int&> ? "True" : "False");
	printf("Is [char]   default destructible? %s\n", is_defalut_destructible_v<char> ? "True" : "False");
	printf("Is [double] default destructible? %s\n", is_defalut_destructible_v<double> ? "True" : "False");
	printf("Is [A]      default destructible? %s\n", is_defalut_destructible_v<A> ? "True" : "False");
	printf("Is [B]      default destructible? %s\n", is_defalut_destructible_v<B> ? "True" : "False");
	printf("\n");

	printf("Is [vector] have push_front()? %s\n", have_push_front_v<std::vector> ? "True" : "False");
	printf("Is [deque]  have push_front()? %s\n", have_push_front_v<std::deque> ? "True" : "False");
	printf("Is [set]    have push_front()? %s\n", have_push_front_v<std::set> ? "True" : "False");
	printf("\n");
}