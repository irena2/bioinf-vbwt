#include "vbwt.h"
#include "string_factorize.h"
#include "merge_sort.h"
#include "string_compare.h"

#include <algorithm>
#include <iostream>

// Rotates given V-word n times
std::vector<std::string> rotate(std::string vword, int n)
{
	std::vector<std::string> rotations;

	int start = 1;
	int length = vword.length() - 1;	

	rotations.push_back(vword);

	while (length && ((n - 1) != 0))
	{
		std::string rvword = vword.substr(start, length) 
			+ vword.substr(0, start);

		rotations.push_back(rvword);	

		start++; length--;
		
		n--;
	}	

	return rotations;
}

// Calculates maximal letter in a given V-word
char max_letter (std::string vword) 
{	
	return vword[0];
}

// Calculates number of maximal letters
// in a given V-word
int max_letter_count (std::string vword)
{
	char g = vword[0];
	int g_counter = 0;

	for (int i = 0, n = vword.length(); i < n; i++)
		if (vword[i] == g)
			g_counter++;

	return g_counter;
}

// Homogenizes V-word by adding substrings starting with
// g to its end repeat number of times
std::string homogenize (std::string vword, int repeat)
{
	int i, j;
	char g = max_letter(vword);

	int last_g = 0;

	for (i = 0; i < repeat; i++)
	{
		for (j = last_g + 1; j < vword.size(); j++)
			if (vword[j] == g)
				break;

		vword += vword.substr(last_g, j - last_g);
		
		last_g = j;
	}

	return vword;
}

// Calculates V-transform for input known to be a vword
std::string vbwt_vword(std::string vword)
{
	std::string vtransform = "";

	// Calculate R
	// that contains all cyclic rotations of an input string 
	// as an n x n matrix
	std::vector<std::string> rotations = rotate(vword, vword.length());
	
	// Calculate R<
	// that contains all the rows of R sorted into increasing V-order
	// using linear-time V-order comparison
	sort(rotations.begin(), rotations.end(), compare);

	// the last column of R< is the V-transform	
	for (int i = 0; i < rotations.size(); i++)
		vtransform.push_back(rotations[i].back());

	return vtransform;
}

std::string vbwt(std::string x)
{
	std::string vtransform = "";

	// Factorize input string into V-words
	// with linear partitioning algorithm
	// for Hybrid Lyndons using V-order
	std::vector<std::string> vwords = factorize(x);

	// If there is only one V-word call simpler
	// function vbwt_vword
	if (vwords.size() == 1)
		return vbwt_vword(vwords[0]);

	/*for (int i = 0; i < r.size(); i++)
		std::cout << r[i] << std::endl;*/

	int i, j;
	// Process V-words in reverse order
	// from right to left
	for (i = vwords.size() - 1; i >= 0 ; i--)
	{
		// Get maximal letter in a vword
		char g = max_letter(vwords[i]);
		
		// Find other group members (can be only right after current V-word
		// in reverse order) and remember how many maximal letters
		// they have for homogenization and how many they should have
		std::vector<std::string> members;
		std::vector<int> members_g_count;

		// Process current V-word
		members.push_back(vwords[i]);
		members_g_count.push_back (max_letter_count(vwords[i]));
		int max_g_count = max_letter_count(vwords[i]);

		// Process other V-words in a group
		for (j = i - 1; j >= 0 && max_letter(vwords[j]) == g; j--)
		{
			members.push_back(vwords[j]);

			int g_count = max_letter_count(vwords[j]);
			members_g_count.push_back (g_count);

			if (max_g_count < g_count)
				max_g_count = g_count;
		}

		// Homogenize V-words to have the same number of letter g as the V-word in
		// a group which has the most and get sorted rotations
		// (watch out for rotations number when homogenized! - homogenize first, but
		// rotate it only - vword.length() before homogenization - times)
		// Or, if homogenization is not needed, just get sorted rotations
		std::vector<std::string> rotations;
		std::vector<std::string> merged_rotations;

		for (int k = 0; k < members.size(); k++)
		{
			int n;

			if (members_g_count[k] != max_g_count)
			{
				n = members[k].size();
				members[k] = homogenize (members[k], max_g_count - members_g_count[k]);
			}
			else
				n = members[k].size();
			
			rotations = rotate(members[k], n);

			// Use sort function instead of suffix-sort to sort
			// rotations of a V-word
			sort(rotations.begin(), rotations.end(), compare);
				
			// Add every rotation in a group to a vector
			// so all rotations of one group can be merge sorted
			for (int l = 0; l < rotations.size(); l++)
				merged_rotations.push_back(rotations[l]);
		}

		// Merge sort all rotations of one group
		/*MergeSort merge;
		merged_rotations = merge.sort (merged_rotations);*/	
		sort(merged_rotations.begin(), merged_rotations.end(), compare);

		// Add last letter of merged rotations to vtransform
		for (int k = 0; k < merged_rotations.size(); k++)
				vtransform.push_back(merged_rotations[k].back());

		// Skip processed V-words and go to next group
		i = j + 1;
	}

	return vtransform;
}
