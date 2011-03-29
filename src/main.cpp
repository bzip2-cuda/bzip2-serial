#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "func.h"

using namespace std;

int main(int argc, char* argv[])
{
    string word, bwt_word;
    int len;
    
    cout << "Hello user!\nPlease enter a string: ";
    cin >> word;
    len = word.length();
    
    bwt(word, bwt_word);
    
    cout << "BWT done. Result: " << bwt_word << endl;
	
	
    
    return 0;
}

