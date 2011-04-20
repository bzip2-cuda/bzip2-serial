#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "bzip2.h"
#include "rle.h"
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
    
    /*stderr::*///cout << "Input file read done. Result:\n" << data << endl;
    cout << data;
    
    bwt(data, bwt_data);
    
    /*stderr::*///cout << "BWT done. Result: " << bwt_data << endl;
	
	mtf(bwt_data, mtf_list, huffman_freq);
	
	/*stderr::*///cout << "MTF done. Result: " << bwt_data << endl;
	
	Hufftree<char, double> hufftree(huffman_freq.begin(), huffman_freq.end());
    huffman_data = hufftree.encode(bwt_data.begin(), bwt_data.end());
    
    /*stderr::*///cout << "Huffman done. Result: " << huffman_data << endl;
    
    ostringstream ss;
    ss << huffman_data;

    string compressedData = encodeRLE(ss.str());

    /*stderr::*///cout << "RLE done. Result: " << compressedData << endl;
    
    file.makeHeader(compressedData);

    file.writeFile();
    
    return 0;
}

