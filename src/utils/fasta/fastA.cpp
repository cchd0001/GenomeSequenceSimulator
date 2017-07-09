#include "fastA.h"
#include "utilsError.hpp"
#include <iostream>

namespace Utils 
{

    FastAReader::FastAReader(const std::string & fname) : file_name(fname)
    {
        reader.open(fname,std::ios::in);
        FATAL_TRUE_EN(reader.is_open(),"FastAReader : %s ... ",file_name.c_str());
    }

#define MAXLINE 1024
    const std::string  FastAReader::GetNextRead() 
    {
        std::string ret;
        if(Eof())
        {
            return ret;
        }
        char buffer[MAXLINE];
        bool init = false;
        while(reader.getline(buffer,MAXLINE))
        {
            if(buffer[0] == '>')
            {
                if( !init) 
                {
                    continue; 
                }
                else
                {
                    return ret;
                }
            }
            ret += std::string(buffer);
        }
        return ret;
    }

    /////////////////////////////////////////////////////////////////////

    #define WEIGHT_MAX 100u

    FastAWriter::FastAWriter(const std::string & fname) 
        : file_name(fname)
        , newline(true)
        , weight(0)
    {
        writer.open(file_name,std::ios::out);
        FATAL_TRUE_EN(writer.is_open());
    }

    void FastAWriter::StartNewRead(const std::string & commond)
    {
        if(!newline)
        {
            writer<<std::endl;
            newline = true;
            weight = 0;
        }
        writer<<'>'<<commond<<std::endl;
    }

    void FastAWriter::WriteRead(const std::string & read)
    {
        size_t curr = 0;

        while(read.length() -curr > WEIGHT_MAX - weight)
        {
            writer<<read.substr(curr, WEIGHT_MAX-weight)<<std::endl;
            curr += WEIGHT_MAX - weight-1;
            weight = 0 ;
            newline = true ;
        }

        if(read.length() - curr > 0 )
        {
            writer<<read.substr(curr);
            weight = read.length() -curr ;
            newline = false;
        }
    }

}//namespace GSS


