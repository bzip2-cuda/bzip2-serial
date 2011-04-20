#ifndef RLE_H
#define RLE_H

#include <iostream>
#include <string>
#include <sstream>
#include <boost/regex.hpp>
#include <cstdlib>

string encodeRLE( const string & to_encode )
{
    string::size_type found = 0 , nextfound = 0 ;
    ostringstream oss ;
    nextfound = to_encode.find_first_not_of( to_encode[ found ] , found ) ;
    while ( nextfound != string::npos )
    {
        oss << nextfound - found ;
        oss << to_encode[ found ] ;
        found = nextfound ;
        nextfound = to_encode.find_first_not_of( to_encode[ found ] , found ) ;
    }
    //since we must not discard the last characters we add them at the end of the string
    string rest ( to_encode.substr( found ) ) ;//last run of characters starts at position found 
    oss << rest.length( ) << to_encode[ found ] ;
    return oss.str( ) ;
}

string decodeRLE ( const string & to_decode )
{
    boost::regex e ( "(\\d+)(\\w)" ) ;
    boost::match_results<string::const_iterator> matches ;
    ostringstream oss ;
    string::const_iterator start = to_decode.begin( ) , end = to_decode.end( ) ;
    while ( boost::regex_search ( start , end , matches , e ) )
    {
        string numberstring ( matches[ 1 ].first , matches[ 1 ].second ) ;
        int number = atoi( numberstring.c_str( ) ) ;
        string character ( matches[ 2 ].first , matches[ 2 ].second ) ;
        for ( int i = 0 ; i < number ; i++ ) 
            oss << character;
        start = matches[ 2 ].second ;
    }
    return oss.str( ) ;
}

#endif
