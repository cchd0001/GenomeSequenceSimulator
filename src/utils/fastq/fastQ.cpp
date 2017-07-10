#include "fastQ.h"
#include "utilsError.hpp"
#include <iostream>

namespace Utils 
{
/*
    FastQReader::FastQReader(const std::string & fname) : file_name(fname)
    {
        reader.open(fname,std::ios::in);
        FATAL_TRUE_EN(reader.is_open(),"FastQReader : %s ... ",file_name.c_str());
    }

#define MAXLINE 1024
    const std::string  FastQReader::GetNextRead() 
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
*/
    /////////////////////////////////////////////////////////////////////

    #define WEIGHT_MAX 100u

    FastQWriter::FastQWriter(const std::string & fname) 
        : file_name(fname)
        , readend(true)
        , newline(true)
        , weight(0)
        , readlen(0)
    {
        writer.open(file_name,std::ios::out);
        FATAL_TRUE_EN(writer.is_open());
    }

    void FastQWriter::StartNewRead(const std::string & commond)
    {
        if(!readend)
        {
            EndRead();
        }
        writer<<'@'<<commond<<std::endl;
    }

    void FastQWriter::WriteRead(const std::string & read)
    {
        readend =false;
        size_t curr = 0;

        readlen += read.length();
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
    void FastQWriter::EndRead()
    {
        if(!newline)
        {
            writer<<std::endl;
            newline = true;
            weight = 0;
        }
        writer<<'+'<<std::endl;
        writer<<std::string(readlen,'I')<<std::endl;
        readlen = 0;
        readend = true;
    }

}//namespace GSS


