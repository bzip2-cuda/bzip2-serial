#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "func.h"

using namespace std;

int main(int argc, char* argv[])
{
    string word;
    int len;
    vector<string> rotations;
    
    cout << "Hello user!\nPlease enter a string: ";
    cin >> word;
    len = word.length();
    
    bwt(word, rotations);
    
    cout << "BWT done. Result:\n";
    for(int i = 0; i < len; i++)
	{
		cout << "\t" <<rotations[i][rotations[i].length()-1] << endl;
	}
    
    return 0;
}

