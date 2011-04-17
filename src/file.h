#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <ostream>
#include <iterator>
#include <cstdlib>

using namespace std;

class fileHandler
{
private:
    string inFile, outFile;
    char *iF, *oF;
public:
    fileHandler(int argC, char*argV[])
    {
        if (argC != 2)
        {
            cout << "Usage: cbz2 INPUTFILE" << endl;
            exit(1);
        }
        inFile = argV[1];
        outFile = inFile;
        outFile += ".cbz2";
        iF = &inFile[0];
        oF = &outFile[0];
    }
    void readFile(string &);

    void writeFile(string );

    void md5(string, string&);

    void makeHeader();

    /*
    Header:
        MD5 hash
        original file name
        if (blocks == 1) //because string::max_size() is 1073741820, which is nearly 1 GB (~0.999999996 GB)
        {
            block location table
            file-padder and adder of beginning and end markers
        } // IDEAL IS A BLOCK SIZE OF 256 MB, SO THAT CUDA CAN ALSO COMFORTABLY HANDLE THE BLOCKS
    */
};
#endif
