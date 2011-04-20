/*
Header:
    MD5 hash
    original file name
    if(blocks == 1) //because string::max_size() is 1073741820, which is nearly 1 GB(~0.999999996 GB)
    {
        block location table
        file-padder and adder of beginning and end markers
    } // IDEAL IS A BLOCK SIZE OF 256 MB, SO THAT CUDA CAN ALSO COMFORTABLY HANDLE THE BLOCKS
*/
    
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
#include <sstream>
#include <boost/regex.hpp>

using namespace std;

class fileHandler
{
private:
    string inFile, outFile, outputForFile;
    string md5sum, blockTable;
    char *iF, *oF;
public:
    ifstream infile;
    ifstream::pos_type fileSize;
    ofstream outfile;
    fileHandler(int argC, char *argV[])
    {
        if(argC != 2)
        {
            cout << "Usage: cbz2 INPUTFILE" << endl;
            exit(1);
        }
        inFile = argV[1];
        outFile = inFile;
        outFile += ".cbz2";
        iF = &inFile[0];
        oF = &outFile[0];
        infile.open(iF, ios::in|ios::binary|ios::ate);
        fileSize = infile.tellg();
        infile.seekg(0, ios::beg);
        outfile.open(oF, ios::out|ios::binary);//|ios::ate);
        
        outputForFile += inFile;
        outputForFile += "\n";
        md5();
        outputForFile += md5sum;
        outputForFile += "\n";
    }
    
    ~fileHandler()
    {
        infile.close();
        outfile.close();
    }
    
    void readFile(string &output, int size)
    {
        if(infile.is_open())
        {
            char *memblock = new char [size];
            infile.read(memblock, size);
            output += memblock;
            /*stderr::*///cout << memblock << endl;
            delete[] memblock;
        }
        else
        {
            cout << "Unable to open file for reading.\n";
            exit(1);
        }
    }

    void writeFile()
    {
        if(outfile.is_open())
        {
            char *memblock = &outputForFile[0];
            ofstream::pos_type size = outputForFile.length();
            
            //outfile.seekg(0, ios::beg);
            outfile.write(memblock, size);
            //delete[] memblock;
            outfile.close();
        }
        else
        {
            cout << "Unable to open file for writing.\n";
            exit(1);
        }
    }

    void md5()
    {
        string command = "cat ";
        command += iF; //We do the md5sum for the whole input file
        command += " | md5sum > tmp";
        char *p = &command[0];
        system(p);
        
        ifstream infile("tmp", ios::in|ios::binary|ios::ate);

        if(infile.is_open())
        {
            ifstream::pos_type size = infile.tellg();
            char *memblock = new char [size];
            infile.seekg(0, ios::beg);
            infile.read(memblock, size);
            string temp = memblock;
            string output(temp, 0, temp.length() - 5);
            md5sum = output;//cout << output << endl;
            infile.close();
            system("rm tmp");
            delete[] memblock;
        }
        else
        {
            cout << "Unable to open file.\n";
            exit(1);
        }
    }
    
    void makeHeader(string &compressedData)
    {
        outputForFile += compressedData; //compressedData has to be RLEd
        outputForFile += "\n";
    }
};
#endif
