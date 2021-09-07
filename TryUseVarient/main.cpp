#include <stdio.h>
#include <variant>
#include <vector>
#include <string>

int main()
{
	using age_t = int;
	using height_t = double;
	using name_t = std::string;
	using gender_t = bool;

	std::variant<age_t, height_t, name_t, gender_t> va;
	va = 5;
	va = 181.4;
}