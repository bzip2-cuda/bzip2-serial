#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <ostream>
#include <iterator>

#define USAGE cout << "Usage: ./main INPUTFILE" << endl

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
    else cout << "Unable to open file.\n";
    exit(1);
}

void writeFile(int argc, char* argv[], string &output)
{
    string filename;
    filename += argv[1];
    filename += ".cbz2";
    cout << filename << endl;
}
