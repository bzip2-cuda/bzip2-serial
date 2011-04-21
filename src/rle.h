#ifndef RLE_H
#define RLE_H

//Header containing the Run-Length Encoding and Decoding functions
//Code modified from http://rosettacode.org/wiki/Run-length_encoding#C.2B.2B
//Thanks!

#include <iostream>
#include <string>
#include <sstream>
#include <boost/regex.hpp>
#include <cstdlib>

string encodeRLE(const string &to_encode) //Takes in a string and returns the encoded string
{
    string::size_type found = 0 , nextfound = 0;
    ostringstream oss;
    nextfound = to_encode.find_first_not_of(to_encode[found] , found);
    while(nextfound != string::npos)
    {
        oss << nextfound - found;
        oss << to_encode[found];
        found = nextfound;
        nextfound = to_encode.find_first_not_of(to_encode[found] , found);
    }
    string rest(to_encode.substr(found));
    oss << rest.length() << to_encode[found];
    return oss.str();
}

string decodeRLE(const string &to_decode) //Takes in a string and returns the decoded string
{
    boost::regex e("(\\d+)(\\w)");
    boost::match_results<string::const_iterator> matches;
    ostringstream oss;
    string::const_iterator start = to_decode.begin(), end = to_decode.end();
    while(boost::regex_search(start , end , matches , e))
    {
        string numberstring(matches[1].first , matches[1].second);
        int number = atoi(numberstring.c_str());
        string character(matches[2].first , matches[2].second);
        for(int i = 0; i < number; i++)
            oss << character;
        start = matches[2].second;
    }
    return oss.str();
}

#endif
