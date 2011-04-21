#ifndef FILE_H
#define FILE_H

//Header containing the file-handling class

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

class fileHandler //Class containing the file-handling data structures and functions
{
private:
    string inFile, outFile, outputForFile;
    string md5sum, blockTable;
    char *iF, *oF;
public:
    ifstream infile;
    ifstream::pos_type fileSize;
    ofstream outfile;
    fileHandler(int argC, char *argV[]) //Constructor. Checks argc for correct program usage, opens input and output files, initialises data
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
    
    ~fileHandler() //Destructor. Closes the input and output files. Default destructor takes care of clean-up.
    {
        infile.close();
        outfile.close();
    }
    
    void readFile(string &output, int size) //Reads size amount of data from file into output
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

    void writeFile() //Writes output into file
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

    void md5() //Calculates MD5 hash for input file
    {
        string command = "cat ";
        command += iF;
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
    
    void makeHeader(string &compressedData) //Adds data to the output for file
    {
        outputForFile += compressedData;
        outputForFile += "\n";
    }
};
#endif
