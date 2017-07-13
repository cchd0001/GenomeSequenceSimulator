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
            return std::unique_ptr<IFileWriter>(new FastAWriter(filename+".fasta"));
        }
        else if( t == GenomeSequenceInfo::FASTQ)
        {
            return std::unique_ptr<IFileWriter>(new FastQWriter(filename+".fastq"));
        }
        return std::unique_ptr<IFileWriter>(nullptr);
    }


    void OutputLogic::Process1Sequence(const GSS::GenomeSequenece & sequence)
    {
        size_t read_num  =  sequence.length()/info.read_length * info.depth;
        std::string commond = "Simulator data , type " 
            + (info.read_type == GenomeSequenceInfo::SINGLE ? std::string("Single") : std::string("Pair-End"))
            + " insert_len " + std::to_string(info.insert_length) 
            + " read_len " + std::to_string(info.read_length)
            + " id ";
        for( int id = 0 ; id < (int)read_num ; id++)
        {
            if(info.read_type == GenomeSequenceInfo::ReadType::SINGLE)
            {
                writer0->StartNewRead(commond + std::to_string(id));
                writer0->WriteRead(sequence.GetFramentSequence(sequence.GetRandomFragment(info.insert_length,rand() & 0x1)));
                writer0->EndRead();
            }
            else
            {
                writer0->StartNewRead(commond + std::to_string(id));
                writer1->StartNewRead(commond + std::to_string(id));
                auto base = sequence.GetRandomFragment(info.insert_length,rand() & 0x1);
                writer0->WriteRead(sequence.GetFramentSequence(base.Head(info.read_length)));
                writer1->WriteRead(sequence.GetFramentSequence(base.Tail(info.read_length)));
                writer0->EndRead();
                writer1->EndRead();
            }
        }
    }
}
