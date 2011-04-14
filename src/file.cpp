#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <ostream>
#include <iterator>

#define USAGE cout << "Usage: cbz2 INPUTFILE" << endl

using namespace std;

void readFile(int argc, char* argv[], string &output)
{
    if (argc < 2)
    {
        USAGE;
        exit(1);
    }
    
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
    if (argc < 2)
    {
        USAGE;
        exit(1);
    }
    
    string filename;
    filename += argv[1];
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
