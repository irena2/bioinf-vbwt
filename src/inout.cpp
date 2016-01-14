#include "inout.h"

// reads sequences from FASTA formatted files
// 	discards descriptions (lines starting with '>')
std::vector<std::string> read_fasta (const char *filename)
{
	std::ifstream file;
	file.open(filename);

	std::vector<std::string> sequences;

	std::string sequence;
	std::string line;

  	while (std::getline(file, line))
	{
    		if (line.size() == 0)
      			continue;
    		else if(line[0] == '>') 
		{
      			if (sequence.size() > 0)
			        sequences.push_back(sequence);
      			
			sequence = "";
    		}
    		else 
      			sequence += line;
 	}

	if (sequence.size() > 0)
    		sequences.push_back(sequence);

  file.close();

  return sequences;
}

// writes the given string to file
void write_to_file(const char *filename, std::string to_write)
{
	std::ofstream file;

	file.open(filename);
	file << to_write;

	file.close();
}
