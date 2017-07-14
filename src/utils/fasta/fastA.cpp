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
    const ReadInfo  FastAReader::GetNextRead() 
    {
        ReadInfo ret;
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
                    std::string line(buffer);
                    size_t spilt_index = line.find_first_of(' ');
                    if(spilt_index > 1 )
                    {
                        ret.name = line.substr(1,spilt_index-1);
                    }
                    if( spilt_index < line.length() -2)
                    {
                        ret.comment = line.substr(spilt_index);
                    }
                    continue; 
                }
                else
                {
                    return ret;
                }
            }
            ret.read += std::string(buffer);
        }
        return ret;
    }

    /////////////////////////////////////////////////////////////////////

    #define WIDTH_MAX 100u

    FastAWriter::FastAWriter(const std::string & fname) 
        : readend(true)
        , newline(true)
        , weight(0)
        , readlen(0)
        , total_n(0)
    {
        fd =fopen(fname.c_str(),"w");
        FATAL_TRUE_EN(fd);
    }

   void FastAWriter::StartNewRead(const std::string & name,int start,int end ,
                int error_count,int snp_count,int indel_count,int index ,bool reverse)
    {
        if(!readend)
        {
            EndRead();
        }
        fprintf(fd,">%s_%u_%u_%d:%d:%d_%d/%d\n",name.c_str(),start,end,error_count,snp_count,indel_count,index,reverse?2:1);
    }

    void FastAWriter::WriteRead(const std::string & read)
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
    void FastAWriter::EndRead()
    {
        if(!newline)
        {
            fprintf(fd,"\n");
        }
        newline = true;
        weight = 0;
        total_n += readlen;
        newline = true;
        weight = 0;
        readlen = 0;
        readend = true;
    }


    FastAWriter::~FastAWriter()
    {
        if(fd)
        {
            fclose(fd);
            fd = 0;
        }
        std::cout<<"Total write "<<total_n<<" bp into file !"<<std::endl;
    }

}//namespace GSS


