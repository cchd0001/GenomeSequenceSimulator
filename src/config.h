#ifndef __GSS_CONFIG_H__
#define __GSS_CONFIG_H__

#include <vector>
#include <string>
#include <functional>

namespace GSS{

struct GenomeSequenceInfo
{
    enum FileType
    {
        FASTA,
        FASTQ,
    };

    enum ReadType
    {
        SINGLE,
        PAIR_END,
        MATE_END,
    };

    FileType file_type;
    ReadType read_type;
    unsigned int read_length;
    unsigned int insert_length;
    unsigned int depth;
    std::string file_name ;
};//struct GenomeSequenceInfo


class Config
{
    public:
        enum InputFileType
        {
            FASTA,
            FASTQ,
        };
    private:

        InputFileType input_file_type;

        std::string source_file;

        std::vector<GenomeSequenceInfo> infos;

    public:
        static Config & Instance();

        inline const std::string SourceFile() const 
        {
            return source_file;
        }

        inline const InputFileType & FileType() const 
        {
            return input_file_type;
        }

        void InitFromJson(const std::string & json_file);

        //void ForEachInfo( void (*f)(const GenomeSequenceInfo& ) ) const ;
        void ForEachInfo(std::function<void(const GenomeSequenceInfo&)> ) const ;

};//class Config

}//namespace GSS

#endif //__GSS_CONFIG_H__
