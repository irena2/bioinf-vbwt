#include "string_factorize.h"

#define SENTINEL_LETTER ('z'+ 1)

// Adds V-word to the given vector
int output(int h, int rep, int l, std::string x, std::vector<std::string>& v_words)
{
	if (l > 0) 
	{
		for (int i = 0; i < rep; i++)
		{
			int old = h;
			h = h + l;
			std::string v_word = x.substr(old, l);
			v_words.push_back(v_word);
    		}
  	}

	return h;
}

// Factorizes the string into V-words
// Algorithm from 'Daykin et al 2013 - A linear partitioning algorithm for
// Hybrid Lyndons using V-order.'
std::vector<std::string> factorize(std::string x)
{
	x += SENTINEL_LETTER;
	std::vector<std::string> v_words;
	int h = 0;
	int n = x.size();
	int i, j, k1, l1, rep, k2, l2;
	char g;

	while (h < n)
	{
		// RESET
		i = h;
		j = h + 1;
		g = x[i];
		k1 = 1;
		l1 = 1;
		rep = 1;
		k2 = 0;
		l2 = 0;
		// END RESET


		while (x[j] <= g)
		{
			if (x[i] == x[j] && x[i] == g) 
			{
				if (j - i == k1) 
				{
					k1++;
					rep++;
				} 
				else
				{
					if (i - h < k1) 
					{
				            k2++;
					}
					
					l2++;
					i++;
				}
			}

			else if (x[j] == g)
			{
				h = output(h, rep, l1, x, v_words);
        
				// RESET
 	       			i = h;
 	       			j = h + 1;
 	       			g = x[i];
 	       			k1 = 1;
 	       			l1 = 1;
 	       			rep = 1;
 	       			k2 = 0;
 	       			l2 = 0;
 	       			// END RESET
				j--;
			}

			else if (x[i] == g)
			{
				if (j == k1)
				{
					l1 = k1 + 1;
				}
				else
				{
					l1 = rep * l1 + 1;
				}
		
				rep = 1;
				i = h;

				if (k2 > 0) 
				{
					l1 += l2;
					k2 = 0;
          				l2 = 0;
				}
			}

			else if (x[i] == x[j]) 
			{
				l2++;
		
				if (l1 == l2)
				{
					rep++;
					k2 = 0;
          				l2 = 0;
					i = h;
				}
        
				else
				{
					i++;
				}
			}

			else 
			{
	        		if (g == SENTINEL_LETTER)
				{
					break;
				}
		
				int j2 = j;
				while (x[j + 1] < g && j < n - 2)
				{
					j++;
        			}
		
				std::string u = x.substr(h, l1);
				std::string v = x.substr(j2 - l2, j - j2 + l2 + 1);

				if (!compare(u, v)) 
				{
					h = output(h, rep, l1, x, v_words);
	        		}
		
				l1 = j - h + 1;
				rep = 1;
				k2 = 0;
				l2 = 0;
				i = h;
			}
	
			j++;
		}
	
		h = output(h, rep, l1, x, v_words);
	}


	std:: string last_word = v_words[v_words.size() - 1];
	
	if (last_word[last_word.size() - 1] == SENTINEL_LETTER)
	{
    		v_words[v_words.size() - 1].pop_back();
	}

  	if (v_words.size() > 1 && v_words[v_words.size() - 1] == "")
	{
    		v_words.pop_back();
  	}

	return v_words;
}
