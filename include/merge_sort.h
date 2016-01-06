#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <string>
#include <vector>

#include "string_compare.h"

class MergeSort
{
	private:
		std::vector<std::string> values;
		std::vector<std::string> values_temp;

		void merge (int left, int middle, int right);
		void merge_sort (int left, int right);
	public:
		std::vector<std::string> sort (std::vector<std::string> strings);			
};

#endif
