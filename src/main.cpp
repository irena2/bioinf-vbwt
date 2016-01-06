#include "string_compare.h"

#include <iostream>

int main(int argv, char **argc)
{
	std::cout << "Compare 3132 < 3232 using V-order" << std::endl;

	std::cout << "Result = " << compare ("3132", "3232") << std::endl;

	return 0;
}
