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
    string data, bwt_data, mtf_list;
    vector<bool> huffman_data;
    std::map<char, double> huffman_freq;
    int dataLength;
    fileHandler file(argc, argv);
    
    file.readFile(data);
    dataLength = data.length();
    
    //cout << "Input file read done. Result:\n" << data << endl;
    
    bwt(data, bwt_data);
    
    //cout << "BWT done. Result: " << bwt_data << endl;
	
	mtf(bwt_data, mtf_list, huffman_freq);
	
	//cout << "MTF done. Result: " << bwt_data << endl;
	
	Hufftree<char, double> hufftree(huffman_freq.begin(), huffman_freq.end());
    huffman_data = hufftree.encode(bwt_data.begin(), bwt_data.end());
    
    //cout << "Huffman done. Result: " << huffman_data << endl;
    
    ostringstream ss;
    ss << huffman_data;
    
    file.writeFile(ss.str());
    
    return 0;
}

