#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "bzip2.h"
#include "file.h"

using namespace std;

int main(int argc, char* argv[])
{
    string word, bwt_word, mtf_list;
    vector<string> huffman_word;
    std::map<char, double> huffman_freq;
    int len;
    
    cout << "Hello user!\nPlease enter a string: ";
    cin >> word;
    len = word.length();
    
    bwt(word, bwt_word);
    
    cout << "BWT done. Result: " << bwt_word << endl;
	
	mtf(bwt_word, mtf_list, huffman_freq);
	
	cout << "MTF done. Result: " << bwt_word << endl;
	
	Hufftree<char, double> hufftree(huffman_freq.begin(), huffman_freq.end());
	
	for (int i = 0; i < bwt_word.length(); i++)
	{
	    huffman_word.push_back(hufftree.encode(bwt_word[i]));
	}
    
    return 0;
}

