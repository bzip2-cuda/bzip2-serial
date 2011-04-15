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

#define USAGE if (argc != 2) { cout << "Usage: cbz2 INPUTFILE" << endl; exit(1); }

using namespace std;

void readFile(int argc, char* argv[], string &output)
{
    USAGE;
    
    ifstream infile (argv[1], ios::in|ios::binary|ios::ate);
    
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

void writeFile(int argc, char* argv[], string input)
{
    USAGE;
    
    string filename = argv[1];
    filename += ".cbz2";
    
    char *fname = &filename[0];
    
    ofstream outfile (fname, ios::out|ios::binary);//|ios::ate);
    
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

void md5(string data, string &md5sum)
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

void makeHeader(int argc, char *argv[])
{
    USAGE;
    
    string filename = argv[1];
}
