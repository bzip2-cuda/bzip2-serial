#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

int main()
{
	vector<string> rotations;
	string word;
	int len, i, j;
	time_t begin, end;
	cout <<"Enter word to perform bwt on ";
	cin >> word;
	begin = time(NULL);
	for (int k = 0; k < 1000; k++)
	{
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
		if (k == 0)
		{
			for(i = 0; i < len; i++)
			{
				cout <<rotations[i][rotations[i].length()-1];
			}
			cout <<endl;
		}
	}
	end = time(NULL);
	cout <<"Time taken = " <<difftime(end, begin) << endl;
}	
