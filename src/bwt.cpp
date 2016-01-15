#include "bwt.h"

#include <cstring>

// Calculates bijective variant of BWT using sais_bwt
std::string bwt (std::string x)
{
	const unsigned char* T = reinterpret_cast <const unsigned char*> (x.c_str());
	unsigned char* U = (unsigned char*) malloc(sizeof(unsigned char) * x.length());
	int* A = (int*) malloc(sizeof(int) * x.length());

	sais_bwt (T, U, A, x.length());

	std::string transform (reinterpret_cast <char*> (U));

	return transform;
}
