#include "logic.h"
#include "fastA.h"
#include "fastQ.h"
#include "utilsError.hpp"

using namespace Utils;

namespace GSS
{

    std::unique_ptr<Utils::IFileReader>  Logic::GetFileReader(const Config & conf) 
    {
        if(conf.FileType() == Config::InputFileType::FASTA)
        {
            return std::unique_ptr<Utils::IFileReader>( new Utils::FastAReader(conf.SourceFile()) );
        }
        /*
        else if( conf.FileType() == Config::InputFileType::FASTQ)
        {
            return std::unique_ptr<Utils::IFileReader>( new Utils::FastQReader(conf.SourceFile()) );
        }*/

        FATAL_TRUE(false,"InputFileType not suppert");
        return std::unique_ptr<IFileReader>(nullptr);
    }
    std::unique_ptr<Utils::IFileWriter>   Logic::GetFileWriter(const GSS::GenomeSequenceInfo::FileType t , const std::string & filename) 
    {
        FATAL_TRUE( t== GenomeSequenceInfo::FASTA || t== GenomeSequenceInfo::FASTQ
                , "read_type not support");

        std::vector<std::unique_ptr<IFileWriter> > ret;
        if(t == GenomeSequenceInfo::FASTA)
        {
            return std::unique_ptr<IFileWriter>(new FastAWriter(filename));
        }
        else if( t == GenomeSequenceInfo::FASTQ)
        {
            return std::unique_ptr<IFileWriter>(new FastQWriter(filename));
        }
        return std::unique_ptr<IFileWriter>(nullptr);
    }
}
