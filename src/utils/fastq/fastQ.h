#ifndef __UTILS_FASTQ_FASTQ_H__
#define __UTILS_FASTQ_FASTQ_H__


#include <string>
#include <fstream>
#include "iFileWR.h"
namespace Utils
{
/*
class FastQReader
{
    private:
        std::string file_name;
        std::ifstream reader;

        FastQReader(const FastQReader & ) ;
        FastQReader & operator=(const FastQReader &);
    public:

        const std::string  GetNextRead() ;

        inline bool Eof() const { return reader.eof();} 

        FastQReader(const std::string & fname);

        ~FastQReader(){ if(reader.is_open()) { reader.close() ; }}
};*/


class FastQWriter : public IFileWriter
{
    private:
        //std::string file_name;
        //std::ofstream writer;
        FILE * fd;

        bool readend;
        bool newline;
        int weight;
        int readlen;
        size_t total_n;

        FastQWriter(const FastQWriter& ) ;
        FastQWriter& operator=(const FastQWriter&);

    public:

        FastQWriter( const std::string & fname);

        ~FastQWriter();

        void StartNewRead(const std::string & comment) override;

        void WriteRead(const std::string & read) override;

        void EndRead() override;
};

}//namespace GSS
#endif //__UTILS_FASTQ_FASTQ_H__
