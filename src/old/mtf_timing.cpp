#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "../bzip2.h"

using namespace std;

#define N 10000 //reps

#define USAGE if (argc != 2) { cout << "Usage: cbz2 INPUTFILE" << endl; exit(1); }

int main(int argc, char *argv[])
{
	string list, word, word1;
	time_t begin, end;
	map<char, double> freq;
	
	
	USAGE;
	
	word = argv[1];
	word1 = word;
	
	for (int i = 0; i != 256; i++)
	{
		string list1;
		list1 = char(i);
		list = list + list1;
		for(int j = 0; j < word.length(); j++)
		{
		    if(char(i) == word[j])
		        freq[char(i)]++;
		}
	}
	
	begin = time(NULL);
	for (long int k = 0; k < N; k++)
	{
	    mtf(word, list, freq);
            //cout << word << endl;
            word = word1;
	}
	end = time(NULL);
	cout <<"Time taken = " <<difftime(end, begin) << "\nIterations = " << N << endl;
	return 0;
}
