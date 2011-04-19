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

using namespace std;

/*class fileHandler
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
    
    void makeBlocks(string*, string&);

    void makeHeader();
};*/

class fileHandler
{
private:
    string inFile, outFile;
    string md5sum;
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
            infile.close();
            delete[] memblock;
        }
        else
        {
            cout << "Unable to open file.\n";
            exit(1);
        }
    }

    void writeFile(string input)
    {
        ofstream outfile (oF, ios::out|ios::binary);//|ios::ate);
        
        if (outfile.is_open())
        {
            char *memblock = &input[0];
            ofstream::pos_type size = input.length();
            
            //outfile.seekg(0, ios::beg);
            outfile.write(memblock, size);
            outfile.close();
        }
        else
        {
            cout << "Unable to open file.\n";
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
            delete[] memblock;
        }
        else
        {
            cout << "Unable to open file.\n";
            exit(1);
        }
    }

    void makeBlockTable(string blocks[], string &table)
    {
        ;
    }

    void makeHeader()
    {
        ;
    }
};
#endif
