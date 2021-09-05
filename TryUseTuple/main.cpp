#include <stdio.h>
#include <tuple>

template <typename T>
void PrintType()
{
	printf("\n%s\n", __FUNCSIG__); // signature of function
}

int main()
{
	std::tuple<int, const char*> tuple1{ 8, "ILLmew" };

	printf("Age  = %d\n", std::get<0>(tuple1));
	printf("Name = %s\n", std::get<1>(tuple1));
	printf("\n");

	printf("Age  = %d\n", std::get<int>(tuple1));
	printf("Name = %s\n", std::get<const char*>(tuple1));
	printf("\n");

	auto tuple2 = std::make_tuple(8, "ILLmew", "Hello!");
	printf("Age  = %d\n", std::get<0>(tuple2));
	printf("Name = %s\n", std::get<1>(tuple2));
	printf("%s\n", std::get<2>(tuple2));
	printf("\n");

	auto& [age, name, desc] = tuple2; // C++ 17, structured binding
	age = 20;
	printf("Age  = %d\n", std::get<0>(tuple2));
	printf("Name = %s\n", std::get<1>(tuple2));
	printf("%s\n", std::get<2>(tuple2));
	printf("\n");

	auto tuple3 = std::make_tuple(20, "ILLmew", "Hello!", "Bye!");
	const char* hi{};
	int age1{};
	
	std::tie(age1, std::ignore, hi, std::ignore) = tuple3;
	printf("Age  = %d\n", age1);
	printf("%s\n", hi);
	printf("\n");

	printf("Count of elements in tuple1: %lld\n", std::tuple_size_v<decltype(tuple1)>);
	printf("Count of elements in tuple2: %lld\n", std::tuple_size_v<decltype(tuple2)>);
	printf("Count of elements in tuple3: %lld\n", std::tuple_size_v<decltype(tuple3)>);

	PrintType<std::tuple_element_t<0, decltype(tuple1)>>();
	PrintType<std::tuple_element_t<1, decltype(tuple1)>>();
}