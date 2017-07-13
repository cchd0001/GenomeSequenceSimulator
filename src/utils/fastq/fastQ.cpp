#include "fastQ.h"
#include "utilsError.hpp"
#include <iostream>
#include <stdio.h>

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

    #define WIDTH_MAX 100

    FastQWriter::FastQWriter(const std::string & fname) 
        : readend(true)
        , newline(true)
        , weight(0)
        , readlen(0)
        , total_n(0)
    {
        fd =fopen(fname.c_str(),"w");
        FATAL_TRUE_EN(fd);
    }

    void FastQWriter::StartNewRead(const std::string & commond)
    {
        if(!readend)
        {
            EndRead();
        }
        fprintf(fd,"@%s\n",commond.c_str());
    }

    void FastQWriter::WriteRead(const std::string & read)
    {
        readend =false;
        size_t curr = 0;

        readlen += read.length();
        while(read.length() -curr > WIDTH_MAX- weight)
        {
            fprintf(fd,"%s\n",read.substr(curr,WIDTH_MAX-weight).c_str());
            curr += WIDTH_MAX- weight-1;
            weight = 0 ;
            newline = true ;
        }

        if(read.length() - curr > 0 )
        {
            fprintf(fd,"%s",read.substr(curr).c_str());
            weight = read.length() -curr ;
            newline = false;
        }
    }
    void FastQWriter::EndRead()
    {
        if(!newline)
        {
            fprintf(fd,"\n");
        }
        newline = true;
        weight = 0;
        size_t curr = 0;
        std::string quality(readlen,'i');
        while(quality.length() -curr > WIDTH_MAX- weight)
        {
            fprintf(fd,"%s\n",quality.substr(curr,WIDTH_MAX-weight).c_str());
            curr += WIDTH_MAX- weight-1;
            weight = 0 ;
            newline = true ;
        }

        if(quality.length() - curr > 0 )
        {
            fprintf(fd,"%s\n",quality.substr(curr).c_str());
            weight = quality.length() -curr ;
            newline = true;
        }
        newline = true;
        weight = 0;
        readlen = 0;
        readend = true;
    }


    FastQWriter::~FastQWriter()
    {
        if(fd)
        {
            fclose(fd);
            fd = 0;
        }
        std::cout<<"Total write "<<total_n<<" bp into file !"<<std::endl;
    }

}//namespace GSS


