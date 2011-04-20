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
    fileHandler(int argC, char *argV[])
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
    void readFile(string &output)
    {
        ifstream infile (iF, ios::in|ios::binary|ios::ate);
        
        if (infile.is_open())
        {
            ifstream::pos_type size = infile.tellg();
            char *memblock = new char [size];
            infile.seekg(0, ios::beg);
            infile.read(memblock, size);
            output += memblock;
            /*stderr::*///cout << memblock << endl;
            infile.close();
            delete[] memblock;
            //md5(output);////////////////////
        }
        else
        {
            cout << "Unable to open file for reading.\n";
            exit(1);
        }
    }

    void writeFile()
    {
        ofstream outfile (oF, ios::out|ios::binary);//|ios::ate);
        
        if (outfile.is_open())
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

    void md5(string data)
    {
        string input = "echo \'";
        input += data;
        input += "\' | md5sum > tmp";
        char *p = &input[0];
        system(p);
        
        ifstream infile ("tmp", ios::in|ios::binary|ios::ate);

        if (infile.is_open())
        {
            ifstream::pos_type size = infile.tellg();
            char *memblock = new char [size];
            infile.seekg(0, ios::beg);
            infile.read(memblock, size);
            string temp = memblock;
            string output (temp, 0, temp.length() - 5);
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

    /*void makeBlockTable(string blocks[])
    {
        ;
    }*/

    void makeHeader(string compressedData)
    {
        outputForFile += inFile;
        outputForFile += "\n";
        //outputForFile += md5sum;///////////////
        outputForFile += "\n";
        outputForFile += compressedData; //compressedData has to be RLEd
    }
};
#endif
