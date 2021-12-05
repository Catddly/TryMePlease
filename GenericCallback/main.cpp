#include <utility>
#include <iostream>
#include <tuple>
#include <functional>

template <typename N>
void print(N v)
{
	std::cout << v << std::endl;
}

template <typename N, typename... Ns>
void print(N v, Ns... vs)
{
	std::cout << v << ", ";
	print(vs...);
}

template <size_t... I>
void print(std::index_sequence<I...>)
{
	print(I...);
}

template <typename Func, typename Tuple, size_t... I>
auto callback(Func&& func, Tuple t, std::index_sequence<I...>)
{
	return func(std::get<I>(t)...);
}

template <typename Func, typename Tuple>
auto callback(Func&& func, Tuple t)
{
	return callback(std::forward<Func>(func), t, std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

template <typename Func, typename... Args>
auto callback(Func&& func, Args... args)
{
	return callback(std::forward<Func>(func), std::make_tuple(args...));
}

class TestClass
{
public:
	typedef std::function<int(int, int)> add_func_t;

	void Test()
	{
		auto generic_lambda = [this](auto&&... args) -> decltype(auto)
		{
			return this->TestClass::Hello(std::forward<decltype(args)>(args)...);
		};
		CatchAddFunc(generic_lambda);
	}

	void CatchAddFunc(add_func_t&& func)
	{
		std::cout << "Catch func!\n";
	}
private:
	int Hello(int a, int b)
	{
		std::cout << a << " + " << b << " = " << a + b << "\n";
		return a + b;
	}
};

int main()
{
	print(std::make_index_sequence<10>{});
	print(std::make_index_sequence<6>{});

	auto lambda = [](int a, double b) -> int
	{
		std::cout << a << ": " << b;
		return 5;
	};

	auto lambda1 = [](int a, int b, int c) -> void
	{
		std::cout << a << " " << b << " " << c << "\nsum: " << a + b + c << std::endl;
	};

	std::cout << "  return: " << callback(lambda, 2, 6.55) << "\n";
	std::cout << "  return: " << callback(lambda, 8, 8454.55) << "\n";
	std::cout << "  return: " << callback(lambda, 999, 5424.55) << "\n";
	callback(lambda1, 8, 9, 5);
	callback(lambda1, 84, 91, 52);

	TestClass testClass;
	testClass.Test();
}