#include "string_compare.h"

#include <vector>

#define MAX_LETTER ('z')	// sentinel letter

struct node_t
{
	char value;
	int left;
	int right;
};

// Prepares x for processing by
// breaking x into vector of node_t
std::vector<node_t> preprocess(std::string x, int length)
{
	x = MAX_LETTER + x + MAX_LETTER;

	std::vector<node_t> nodes;

	for (int i = 0; i <= length + 1; i++)
		nodes.push_back({x[i], i-1, i+1});
	
	return nodes;
}

// Deletes letter in string x
std::pair<int,int> del (std::vector<node_t>& x, int i)
{
	int prev = x[i].left;

	while (x[i].value >= x[prev].value)
	{
		i = prev;
		prev = x[i].left;
	}

	int d = i;
	i = x[d].right;

	x[i].left = prev;
	x[prev].right = i;

	return std::make_pair(d, i);
}

// Reduces string x2 to be the same size as x1
std::pair<int,int> reduce (std::vector<node_t>& x2, int length2, int length1)
{
	std::pair<int,int> d = std::make_pair(0, length2 + 1);

	for (int i = 1; i <= length2 - length1; i++)
		d = del (x2, d.second);

	return d;
}

// Calculates longest matching suffix
std::pair<int,int> LMS (std::vector<node_t>& x1, int l1, std::vector<node_t>& x2, int l2)
{
	int i1 = x1[l1].left;
	int i2 = x2[l2].left;

	while (i1 > 0 && x1[i1].value == x2[i2].value)
	{
		i1 = x1[i1].left;
		i2 = x2[i2].left;
	}

	return std::make_pair(x1[i1].right, x2[i2].right);
}

// Compares two input strings
// Algorithm from 'Daykin et al 2013 - A linear partitioning algorithm for
// Hybrid Lyndons using V-order.'
bool compare(std::string x1, std::string x2)
{
	int n1 = x1.length();
	int n2 = x2.length();

	if (n1 > n2)
		return !compare(x2, x1);

	if (x1 == x2)
		return false;

	std::vector<node_t> v_x1 = preprocess(x1, n1);
	std::vector<node_t> v_x2 = preprocess(x2, n2);

	std::pair<int,int> d2 = reduce (v_x2, n2, n1);

	std::pair<int,int> l = LMS (v_x1, n1 + 1, v_x2, n2 + 1);

	if (v_x1[l.first].left == 0)
		return true;

	std::pair<int,int> d1 = std::make_pair(0, n1 + 1);

	int remember1, remember2;
	do
	{
		// Different from pseudocode,
		// used for memorizing the rightest position
		// in x1 and x2, where x1 and x2 differ
		remember1 = v_x1[l.first].left;		
		remember2 = v_x2[l.second].left;

		d1 = del (v_x1, d1.second);
		d2 = del (v_x2, d2.second);

		if (d1.first == l.first || d2.first == l.second)
		{
			l.first = v_x1[l.first].right;
			l.second = v_x2[l.second].right;
		}
		else if (d1.second == l.first || d2.second == l.second)
			l = LMS (v_x1, l.first, v_x2, l.second);		

	} while (v_x1[l.first].left != 0);

	return (v_x1[remember1].value < v_x2[remember2].value);
}
