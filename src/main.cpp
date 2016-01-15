#include "inout.h"
#include "vbwt.h"
//#include "bwt.h"

#include <assert.h>
#include <time.h>

#include <cstdlib>
#include <iostream>
#include <vector>

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
		std::vector<std::string> input = read_fasta (argv[1]);
		std::string output = "";		

		for (int i = 0; i < input.size(); i++)
		{
			clock_t start = clock();

  			output /*+= bwt(input[i]) + '\n'*/;

			clock_t stop = clock();

			double elapsed = double (stop - start) / CLOCKS_PER_SEC;

			printf("Time taken: %.2fs\n", elapsed);

			write_to_file(argv[2], output);
		}
	}
	else if (mode == "vbwt")
	{
		std::vector<std::string> input = read_fasta (argv[1]);
		std::string output = "";

		for (int i = 0; i < input.size(); i++)
		{
			clock_t start = clock();

  			output += vbwt(input[i]) + '\n';

			clock_t stop = clock();

			double elapsed = double (stop - start) / CLOCKS_PER_SEC;

			printf("Time taken: %.2fs\n", elapsed);

			write_to_file(argv[2], output);
		}
	}
	else
		std::cout << "Invalid mode. Use bwt or vbwt." << std::endl;

	return 0;
}
