//Burrows-Wheeler Transform and the reverse

# include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include<time.h>

using namespace std;

void bwt(string word, string &bwt_word)
{
	int len, i, j;
	vector<string> rotations;
	
	rotations.push_back(word);
	len  = word.length();
	
	for (i = 1; i < len; i++)
	{	
		string rot_word;
		rot_word.append(word.substr(i, len -1));
		rot_word.append(word.substr(0, i));
		rotations.push_back (rot_word);
	}
	
	sort (rotations.begin(), rotations.end());
	
	for(int i = 0; i < len; i++)
	{
		bwt_word += rotations[i][rotations[i].length()-1];
	}
	//cout <<"Transformed word : " << bwt_word << endl;
}

int main(int argc, char *argv[])
{
	string word, bwt_word;
	word = argv[1];
	int i;
	word += word[word.length()];
	for ( i = word.length() - 2; i >= 0; i--)
	{
		word[i+1]  = word[i];
	}
	word[0] = char(0);
	word += char(255);
	
	struct timespec t0, t1;
	struct timespec *pt0, *pt1;
	pt0 = &t0;
	pt1 = &t1;
	
	clock_gettime(0, pt0);
	bwt(word, bwt_word);
	clock_gettime(0, pt1);
	
	cout << t1.tv_nsec - t0.tv_nsec << endl;
}
