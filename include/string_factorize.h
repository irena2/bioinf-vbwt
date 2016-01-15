#ifndef STRING_FACTORIZE_H
#define STRING_FACTORIZE_H

#include "string_compare.h"

#include <string>
#include <vector>

// Factorizes string x to V-words
// using linear partitioning algorithm for
// Hybrid Lyndons using V-order
std::vector<std::string> factorize(std::string x);

#endif
