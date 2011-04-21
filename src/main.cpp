#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include "bzip2.h"
#include "rle.h"
#include "file.h"

#define BLOCK_SIZE 256

using namespace std;

void compress(fileHandler);

int main(int argc, char* argv[])
{
    fileHandler file(argc, argv); //Initialise

    while(!(file.infile.eof()))
    {
        string data, bwt_data, mtf_list;
        vector<bool> huffman_data;
        std::map<char, double> huffman_freq;
        ostringstream ss;

        file.readFile(data, BLOCK_SIZE); //Read blocks
        bwt(data, bwt_data);
        mtf(bwt_data, mtf_list, huffman_freq);
        Hufftree<char, double> hufftree(huffman_freq.begin(), huffman_freq.end());
        huffman_data = hufftree.encode(bwt_data.begin(), bwt_data.end());
        ss << huffman_data;
        string compressedData = encodeRLE(ss.str());
        file.makeHeader(compressedData);
    }
    file.writeFile();

    return 0;
}