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

void readFile(int, char**, string &);

void writeFile(int, char**, string );

void md5(string, string&);

void makeHeader(int, char**);

/*
Header:
    MD5 hash
    original file name
    block location table
    block size (12 B)
    file-padder and adder of beginning and end markers
*/

#endif
