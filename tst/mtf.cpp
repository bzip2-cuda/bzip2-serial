#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

int main()
{
	string list, word;
	int i, index;
	time_t begin, end;
	cout <<"Enter word to perform mtf with ";
	cin >> word;
	int k = 0;
	begin = time(NULL);
	for (; k < 1000; k++)
	{
		for (i = 0; i != 256; i++)
		{
			string list1;
			list1 = char(i);
			list = list + list1;
		}
		//Comparing character with the string
		for (i = 0; i < word.length(); i++)
		{
			for (index = 0; ; index++)                 //scan the whole array, no need of end condition
			{
				if (word[i] == list[index]) //till we found it
					break;    //then, break the for
			}
			//Putting found byte in front
			for ( ; index != 0; index--)      //scan from the position of the byte to 0
			{	
				list[index] = list[index-1];  //move all of them to the right
			}
			list[0] = word[i];                      //update the order 0
		}
		for (i = 0; i <= word.length() && k == 0; i++)
			cout << i << "\t" << list[i] << endl;
	}
	end = time(NULL);
	cout <<"Time taken = " <<difftime(end, begin) << endl;
}
