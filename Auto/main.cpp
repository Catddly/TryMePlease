#include <stdio.h>
#include <string>

///-------------------------------------------------------------------------------
///
/// lvalue reference and rvalue reference are type category.
/// lvalue and rvalue are value category.
/// 
/// Something that is a reference, means that it reference to a block of memory.
/// Something that have memory and its memory is accessible, it is lvalue.
/// Something that does not have permanent(we say permanent here which is relative to the life cycle of the program or app) memory
/// is called rvalue or xvalue. (x stands for expire)
/// 
///	e.g.
///  
/// int a = 2;
/// 
/// a here has permanent memory, so a is lvalue.
/// 2 does not have permanent memory, so 2 is rvalue or we can say pure rvalue(prvalue).
/// 
/// int& r = a;
/// int&& rr = 2;
/// 
/// r's type category is lvalue reference, r's value category is lvalue.
/// rr's type category is rvalue reference, rr's value category is lvalue (because its memory is accessible).
/// 
/// auto& ar = a;
///
/// ar's type category is lvalue reference
/// 
/// auto& can ONLY reference to lvalue. auto& can NOT reference to rvalue.
/// but auto&& can reference to both lvalue and rvalue.
/// 
/// int&& rra = 2;
/// auto&& rrrra = rra;
/// 
/// HERE rra's type category is rvalue reference.
/// but rrrra's type category is lvalue reference. (because reference is lvalue!)
/// 
/// And since auto&& can reference to any value, we called it "Generic Reference"
/// 
/// int   as value category, it is prvalue.
/// int&  as value category, it is lvalue.
/// int&& as value category, it is xvalue or eXpiring rvalue.
/// 
/// 
/// auto           as function's return type, it decays the return type.
/// decltype(auto) as function's return type, it preserves the return type.
/// 
///-------------------------------------------------------------------------------

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

#define TypeCategory(VALUE)  TypeToString<decltype(VALUE)>().c_str()
#define ValueCategory(VALUE) TypeToString<decltype((VALUE))>().c_str()

int main()
{
	int a = 2;
	auto& r = a;
	//auto& pr = 2; // Can't work!

	auto&& rr = a;  // ok
	auto&& prr = 2; // ok

	int&& rra = 2;
	auto&& rrrra = rra;

	printf("rra's type category is %s\n", TypeCategory(rra));
	printf("rra's value category is %s\n", ValueCategory(rra));
	printf("rrrra's type category is %s\n", TypeCategory(rrrra));
	printf("rrrra's value category is %s\n", ValueCategory(rrrra));

	auto lambda_decay = [](int a, int b) -> auto
	{
		int* ptr = new int(a + b);
		int& r = *ptr;
		return r;
	};

	auto lambda_preserve = [](int a, int b) -> decltype(auto)
	{
		int* ptr = new int(a + b);
		int& r = *ptr;
		return r;
	};

	auto lambda_expire_d = [](int a, int b) -> auto
	{
		int local = a + b;
		return std::move(local);
	};

	auto lambda_expire_p = [](int a, int b) -> decltype(auto)
	{
		int local = a + b;
		return std::move(local);
	};

	printf("lambda_decay's type category is %s\n", TypeCategory(lambda_decay(1, 2)));
	printf("lambda_preserve's type category is %s\n", TypeCategory(lambda_preserve(1, 2)));
	printf("lambda_expire_d's type category is %s\n", TypeCategory(lambda_expire_d(1, 2)));
	printf("lambda_expire_p's type category is %s\n", TypeCategory(lambda_expire_p(1, 2)));

}