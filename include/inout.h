#ifndef INOUT_H
#define INOUT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// reads sequences from FASTA formatted files
std::vector<std::string> read_fasta (const char *filename);

// writes the given string to file
void write_to_file(const char *filename, std::string to_write);

#endif
