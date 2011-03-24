#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <ostream>
#include <iterator>

using namespace std;

void bwt(string word, vector<string> &rotations)
{
	int len, i, j;
	
	rotations.push_back (word);
	len  = word.length();
	
	for (i = 1; i < len; i++)
	{	
		string rot_word;
		rot_word.append(word.substr(i, len -1));
		rot_word.append(word.substr(0, i));
		rotations.push_back (rot_word);
	}
	
	sort (rotations.begin(), rotations.end());
	
	return rotations;
}

void mtf(string word, string &list)
{
	int counter, index;
	for (counter = 0; counter != 256; counter++)
	{
		string list1;
		list1 = char(counter);
		list = list + list1;
	}
	
	for (counter = 0; counter < word.length(); counter++)
	{
		for (index = 0; ; index++)
		{
			if (word[counter] == list[index])
				break;
		}
		
		for ( ; index != 0; index--)
		{	
			list[index] = list[index-1];
		}
		list[0] = word[counter];
	}
}


