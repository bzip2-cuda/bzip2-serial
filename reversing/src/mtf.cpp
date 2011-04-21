//Move-To-Front Transform and reverse

# include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void mtf(string &word, string &list, map<char, double> &frequencies)
{
	int i, index;
	for (i = 0; i != 256; i++)
	{
		string list1;
		list1 = char(i);
		frequencies[char(i)] = 0; //***
		list = list + list1;
	}
	
	for (i = 0; i < word.length(); i++)
	{
		for (index = 0; index != 256 ; index++)
		{
			if (word[i] == list[index])
		    {
			    frequencies[word[i]]++; //frequencies[char(index)]++; //***
				break;
			}
		}
		
		for ( ; index != 0; index--)
		{	
			list[index] = list[index-1];
		}
		list[0] = word[i];
	}
		
	//MTF encoding
	cout <<"Encoded word: ";
	for (i = 0; i < word.length(); i++)
	{
		for (index = 0; index != 256 ; index++)
		{
			if (word[i] == list[index])
			{
				word[i]=char(index);
				cout << word[i];
				break;
			}
		}
	}
	cout << endl;
}

void mtf_reverse(string &word, string &list)
{
	int i, j;
	for (i = 0; i < word.length(); i++)
	{
		word[i] = list[char(word[i])];
	}
	cout << "Decoded word: " << word << endl;
}

int main(int argc, char *argv[])
{
	string list, word;
	std::map<char, double> huffman_freq;
	word = argv[1];
	mtf(word, list, huffman_freq);
	mtf_reverse(word, list);
}
