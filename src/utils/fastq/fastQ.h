#ifndef __UTILS_FASTQ_FASTQ_H__
#define __UTILS_FASTQ_FASTQ_H__


#include <string>
#include <fstream>

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


class FastQWriter
{
    private:
        std::string file_name;
        std::ofstream writer;

        bool readend;
        bool newline;
        int weight;
        int readlen;

        FastQWriter(const FastQWriter& ) ;
        FastQWriter& operator=(const FastQWriter&);

    public:

        FastQWriter( const std::string & fname);

        ~FastQWriter() { if( writer.is_open()) { writer.close();}}

        void StartNewRead(const std::string & comment);

        void WriteRead(const std::string & read);

        void EndRead();
};

}//namespace GSS
#endif //__UTILS_FASTQ_FASTQ_H__
