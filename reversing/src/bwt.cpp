# include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
	cout <<"Transformed word : " << bwt_word << endl;
}

void bwt_reverse(string word, string bwt_word)
{
	int len, i, j;
	vector<string> rotations;
	
	rotations.push_back(bwt_word);
	len  = bwt_word.length();
	
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
		if (rotations[i][rotations[i].length()-1] == char(255))
			word = rotations[i];
	}
	cout <<"Original word: " << word << endl;
/*
create empty table

repeat length(s) times
insert s as a column of table before first column of the table
sort rows of the table alphabetically
return (row that ends with the 'EOF' character)
*/
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
	bwt(word, bwt_word);
	bwt_reverse(word, bwt_word);
}
