#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <ostream>
#include <iterator>

using namespace std;

template<typename DataType, typename Frequency> class Hufftree;

ostream& operator<<(ostream&, vector<bool>);

void bwt(string, string &);

void mtf(string &, string &, std::map<char, double> &);

//void file-hasher MD5 / SHA / base64?

//store original file name

//store block location table

//store block size (100 kB)

//void file-padder (also adds beginning and end markers)

void readFile(string &);

#endif
