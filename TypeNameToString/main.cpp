#include <stdio.h>
#include <string>

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

struct Test
{
};

struct MyNameIsTypeTypeChan
{
};

class A
{
};

class TestPray
{

};

int main()
{
	printf("typename = %s\n", TypeToString<int>().c_str());
	printf("typename = %s\n", TypeToString<double>().c_str());
	printf("typename = %s\n", TypeToString<const char*>().c_str());
	printf("typename = %s\n", TypeToString<Test>().c_str());
	printf("typename = %s\n", TypeToString<MyNameIsTypeTypeChan>().c_str());
	printf("typename = %s\n", TypeToString<A>().c_str());
	printf("typename = %s\n", TypeToString<TestPray>().c_str());
}