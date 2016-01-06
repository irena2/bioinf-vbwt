#include "merge_sort.h"

void MergeSort :: merge (int left, int middle, int right)
{
	int i;
	int j;
	int k;

	for (i = left; i <= right; i++)
		values_temp[i] = values[i];

	i = left;
	j = middle + 1;
	k = left;

	while (i <= middle && j <= right)
	{
		if (compare (values_temp[i], values_temp[j]))
		{
			values[k] = values_temp[i];
			i++;	
		}
		else
		{
			values[k] = values_temp[j];
			j++;
		}
		k++;	
	}

	while (i <= middle)
	{
		values[k] = values_temp[i];
		k++;
		i++;
	}
}

void MergeSort :: merge_sort (int left, int right)
{
	if (left < right)
	{
		int middle = left + (right - left) / 2;

		merge_sort (left, middle);
		merge_sort (middle + 1, right);

		merge (left, middle, right);
	}
}

std::vector<std::string> MergeSort :: sort (std::vector<std::string> strings)
{
	values = strings;
	
	std::vector<std::string> temp(values.size(), "");
	values_temp = temp;

	merge_sort (0, values.size() - 1);

	return values;
}
