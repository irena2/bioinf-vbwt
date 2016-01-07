#include "vbwt.h"

#include <iostream>
#include <unordered_map>

/* print_groups */
void print_groups (std::unordered_map<char,std::vector<std::string>> groups)
{
	for(auto& group:groups)
	{
		std::cout << "group " << group.first << ":" << std::endl;
		
		for (auto it = group.second.begin(); it != group.second.end(); it++)	
			std::cout << " => " + *it << std::endl;
	}	
}

/* largest_occurring_letter */
char largest_occurring_letter (std::string vword)
{	
	char letter = vword[0];

	for (int i = 1; i != vword.length(); i++)
		if (letter < vword[i])
			letter = vword[i];	

	return letter;
}

/* group */
std::unordered_map<char,std::vector<std::string>> group (std::vector<std::string> vwords)
{
	std::unordered_map<char,std::vector<std::string>> groups;

	for (auto it = vwords.rbegin(); it != vwords.rend(); it++)
	{
		std::string vword = *it;

		if (vword.empty() == true)
			continue;

		char group_name = largest_occurring_letter (vword);

		std::unordered_map<char,std::vector<std::string>>::iterator groups_it;
		groups_it = groups.find(group_name);

		if (groups_it == groups.end())
		{
			std::vector<std::string> group;
			group.push_back(vword);
			groups.insert({group_name, group});
		}
		else
			groups_it->second.push_back(vword);			
	}

	return groups;
}


/* longest_occurring_vword_length */
int longest_occurring_vword_length (std::vector<std::string> vwords)
{
	int length = 0;

	for (auto it = vwords.begin(); it != vwords.end(); it++)
	{
		std::string vword = *it;

		if (length < vword.length())
			length = vword.length();
	}

	return length;
}

/* homogenize */
std::unordered_map<char,std::vector<std::string>> homogenize 
	(std::unordered_map<char,std::vector<std::string>> groups)
{
	int g_length;
	int v_length;
	int add_length;

	for(auto& g:groups)
	{
		g_length = longest_occurring_vword_length (g.second);
		
		for (auto it = g.second.begin(); 
				it != g.second.end(); it++)
		{
			std::string vword = *it;

			v_length = vword.length();
			add_length = g_length - v_length;

			if (add_length > 0)
			{
				int repeat = add_length / v_length;

				std::string word;

				for (int i = 0; i <= repeat; i++)
					word += vword.substr(0, v_length);
				
				word = word.substr(word.length() - add_length, 
							add_length);
				
				(*it) = word + vword;
			}
		}	
	}

	return groups;
}

std::string vbwt (std::vector<std::string> vwords)
{
	std::string vtransform;

	std::unordered_map<char,std::vector<std::string>> groups;
	groups = group (vwords);

	print_groups (groups);

	groups = homogenize (groups);

	std::cout << std::endl;
	print_groups (groups);

	return vtransform;
}
