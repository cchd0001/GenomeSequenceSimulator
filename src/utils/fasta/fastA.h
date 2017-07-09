#ifndef __UTILS_FASTA_FASTQ_H__
#define __UTILS_FASTA_FASTQ_H__


#include <string>
#include <fstream>

namespace Utils
{

class FastAReader
{
    private:
        std::string file_name;
        std::ifstream reader;

        FastAReader(const FastAReader & ) ;
        FastAReader & operator=(const FastAReader &);
    public:

        const std::string  GetNextRead() ;

        inline bool Eof() const { return reader.eof();} 

        FastAReader(const std::string & fname);

        ~FastAReader(){ if(reader.is_open()) { reader.close() ; }}
};


class FastAWriter
{
    private:
        std::string file_name;
        std::ofstream writer;

        bool newline;
        int weight;

        FastAWriter(const FastAWriter& ) ;
        FastAWriter& operator=(const FastAWriter&);

    public:

        FastAWriter( const std::string & fname);

        ~FastAWriter() { if( writer.is_open()) { writer.close();}}

        void StartNewRead(const std::string & comment);

        void WriteRead(const std::string & read);
};

}//namespace GSS
#endif //__UTILS_FASTA_FASTA_H__
