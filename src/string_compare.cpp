#include "string_compare.h"

#include <iostream>
#include <vector>

#define MAX_LETTER "z"

int del (std::string *x, int *i)
{
	if ((*x).length() <= *i)
		*i = (*x).length() - 1;
	
	int delta = *i;

	while (delta > 0 && (*x)[delta] >= (*x)[delta - 1])
		delta--;
	
	if (delta != 0)	
		(*x).erase(delta, 1);

	*i = delta + 1;

	return delta;
}

int reduce (std::string *x, int n)
{
	int i = (*x).length() - 1;

	for (int j = 1; j <= n; j++)
		del (x, &i);

	return i;
}

std::vector<int> LMS (std::string x1, int l1, std::string x2, int l2)
{
	std::vector<int> l;

	int i1 = l1 - 1;
	int i2 = l2 - 1;

	while (x1[i1] == x2[i2] && i1 > 0)
	{
		i1--;
		i2--;
	}

	l.push_back(i1 + 1);
	l.push_back(i2 + 1);

	return l;
}

bool compare (std::string x1, std::string x2)
{
	//x1 > x2
	int n1 = x1.length();
	int n2 = x2.length();

	x1 = MAX_LETTER + x1 + MAX_LETTER;
	x2 = MAX_LETTER + x2 + MAX_LETTER;

	int i1 = n1 + 1;
	int i2 = reduce (&x2, n2 - n1);

	n2 = n1;	

	std::vector<int> l = LMS (x1, n1 + 1, x2, n2 + 1);

	if (l[0] - 1 == 0)
		return true;

	std::string child1, child2;
	int delta, delta1, delta2;
	
	do
	{
		child1 = x1;
		child2 =x2;

		delta1 = del (&x1, &i1);
		delta2 = del (&x2, &i2);

		if (delta1 < delta2)
			delta = delta2;
		else
			delta = delta1;

		l = LMS (x1, l[0], x2, l[1]);		

	} while (l[0] - 1 != 0);

	if (child1[delta] < child2[delta])
		return true;
	else
		return false;
}
