#include <stdio.h>
#include <string>

////////////////////////////////////////////////////////////////////////////////////
/// 
/// Type Category and Value Category
/// 
/// Type Category  -- declared type or deduced type.
/// [ lvalue reference, rvalue reference ]
/// 
/// Value Category -- defined if we can access, assign or modify the expression.
/// [ lvalue, glvalue, rvalue, prvalue, xvalue ]
/// 
/// p of prvalue means "pure"
/// x of xvalue  means "expiring"
/// (prvalue and xvalue) together called rvalue
/// 
/// g of glvalue means "generalized"
/// Both lvalue and xvalue are modifiable and accessible,
/// they are called glvalue.
/// 
/// glvalue = lvalue or xvalue.
/// rvalue = prvalue or xvalue.
/// 
/// lvalue is different from lvalue reference,
/// rvalue is different from rvalue reference,
/// they have different meaning, and they have are defined in different category.
/// They have different concept.
/// 
/// Lvalue have its memory address in runtime, that means system will allocate memory for it.
/// Most of the lvalues have FIXED memory address.
/// Lvalue stores in memory and will be loaded in L1 L2 L3 buffer in CPU to use.
/// Lvalue's memory will be returned to system when it is out of scope or manually destroyed.
/// 
/// Rvalue have no address in runtime, that means system will not allocate memory for it.
/// Rvalue stores in the CPU's registe for temporary computation usage.
/// 
/// Prvalue do not have accessible memory address, usually resides in CPU registe,
/// and it is used to initialize lvalue.
/// 
/// Xvalue has temporary accessible memory address or exist in the CPU registe which 
/// can be modified or accessed by the programmer.
/// 
/// Basically, lvalue means "the value we can modify or access".
/// (i.e. the value of the expression can is assignable)
/// rvalue means "we can not access or modify the value of the expression"
/// 
/// We can get the type  category of expression by using decltype().
/// We can get the value category of expression by using decltype(()).
/// 
////////////////////////////////////////////////////////////////////////////////////

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
	int   a = 6;
	// a's declared type is [int]
	// 6 has no declared type, but its deduced type is [int]
	// 6's type  category is [int&]  (called rvalue reference)
 	// 6's value category is [int&&] (called prvalue)
	printf("Type  category of a is %s\n", TypeCategory(a));
	printf("Value category of a is %s\n", ValueCategory(a));
	printf("\n");

	int&  r = a;
	// r's type  category is [int&] (called lvalue reference)
	// r's value category is [int&] (called lvalue)
	printf("Type  category of r is %s\n", TypeCategory(r));
	printf("Value category of r is %s\n", ValueCategory(r));
	printf("\n");

	int&& rr = 9;
	// rr's type  category is [int&&] (called rvalue reference)
	// rr's value category is [int&]  (called lvalue)
	printf("Type  category of rr is %s\n", TypeCategory(rr));
	printf("Value category of rr is %s\n", ValueCategory(rr));
	printf("\n");
}