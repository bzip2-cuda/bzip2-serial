#include <iostream>
#include <sstream>
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
    vector<bool> huffman_word;
    std::map<char, double> huffman_freq;
    int len;
    
    /*cout << "Hello user!\nPlease enter a string: ";
    cin >> word;
    len = word.length();*/
    
    readFile(argc, argv, word);
    len = word.length();
    
    //cout << "Input file read done. Result:\n" << word << endl;
    
    bwt(word, bwt_word);
    
    //cout << "BWT done. Result: " << bwt_word << endl;
	
	mtf(bwt_word, mtf_list, huffman_freq);
	
	//cout << "MTF done. Result: " << bwt_word << endl;
	
	Hufftree<char, double> hufftree(huffman_freq.begin(), huffman_freq.end());
    huffman_word = hufftree.encode(bwt_word.begin(), bwt_word.end());
    
    //cout << "Huffman done. Result: " << huffman_word << endl;
    
    ostringstream ss;
    ss << huffman_word;
    
    writeFile(argc, argv, ss.str());
    
    return 0;
}

