#include "merge_sort.h"
#include "string_compare.h"

#include <iostream>
#include <vector>

int main(int argv, char **argc)
{
	std::cout << "Compare 3132 < 3232 using V-order" << std::endl;
	std::cout << "Result = " << compare ("3132", "3232") << std::endl;

	std::cout << std::endl;
	std::cout << "Merge sort rotations using V-order string comparison" << std::endl;

	std::vector<std::string> rotations;	
	rotations.push_back("5312543");	
	rotations.push_back("3125435");
	rotations.push_back("1254353");
	rotations.push_back("2543531");
	rotations.push_back("5435312");
	rotations.push_back("4353125");
	rotations.push_back("3531254");

	std::cout << "Rotations = ";
	for (int i = 0; i < rotations.size(); i++)
		std::cout << rotations[i] << " ";
	
	MergeSort merge;
	rotations = merge.sort(rotations);

	std::cout << std::endl;
	std::cout << "Sorted rotations = ";
	for (int i = 0; i < rotations.size(); i++)
		std::cout << rotations[i] << " ";

	return 0;
}
