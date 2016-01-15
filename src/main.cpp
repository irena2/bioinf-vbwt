#include "inout.h"
#include "vbwt.h"

#include <assert.h>
#include <time.h>

#include <cstdlib>
#include <iostream>
#include <vector>

double overallExecutionTimeVBWT(std::string input)
{
	clock_t start = clock();

  	//vbwt(input);

	clock_t stop = clock();

	double elapsed = double (stop - start) / CLOCKS_PER_SEC;

	printf("Time taken: %.2fs\n", elapsed);

	return elapsed;
}

double overallExecutionTimeBWT(std::string input)
{
	clock_t start = clock();

  	//bwt(input);

	clock_t stop = clock();

	double elapsed = double (stop - start) / CLOCKS_PER_SEC;

	printf("Time taken: %.2fs\n", elapsed);

	return elapsed;

}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		std::cout << "Usage: " << argv[0] << " <input> <output> <bwt|vbwt>" << std::endl;

		return (-1); 
	}

	std::string mode(argv[3]);

	if (mode == "bwt")
	{
		std::vector<std::string> v = read_fasta (argv[1]);
		
		for (int i = 0; i < v.size(); i++)
			overallExecutionTimeBWT(v[i]);	
	}
	else if (mode == "vbwt")
	{	
		std::vector<std::string> v = read_fasta (argv[1]);
		
		for (int i = 0; i < v.size(); i++)
			overallExecutionTimeVBWT(v[i]);
	}
	else
		std::cout << "Invalid mode. Use bwt or vbwt" << std::endl;

	return 0;
}
