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

#define USAGE if (argC != 2) { cout << "Usage: cbz2 INPUTFILE" << endl; exit(1); }

using namespace std;
class fileHandler
{
private:
    /*int argC;
    char *argV[];*/
    string inFile, outFile;
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

    void makeHeader()
    {
        ;
    }
};
