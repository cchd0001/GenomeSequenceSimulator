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


    void OutputLogic::Process1Sequence(const GSS::GenomeSequenece & sequence,double error_rate)
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
                auto frament = sequence.GetRandomFragment(info.insert_length,rand() & 0x1);
                auto frament_seq = sequence.GetFramentSequence(frament,error_rate);

                writer0->StartNewRead(sequence.name,frament.start_index,frament.end_index,
                        frament_seq.error_count,frament_seq.snp_count,frament_seq.indel_count,
                        id,frament.reverse);
                writer0->WriteRead(frament_seq.sequence);
                writer0->EndRead();
            }
            else
            {
                auto frament = sequence.GetRandomFragment(info.insert_length,rand() & 0x1);
                auto frament0 = frament.Head(info.read_length);
                auto frament1 = frament.Tail(info.read_length);
                auto frament_seq0 = sequence.GetFramentSequence(frament0,error_rate);
                auto frament_seq1 = sequence.GetFramentSequence(frament1,error_rate);

                writer0->StartNewRead(sequence.name,frament0.start_index,frament0.end_index,
                        frament_seq0.error_count,frament_seq0.snp_count,frament_seq0.indel_count,
                        id,frament0.reverse);

                writer1->StartNewRead(sequence.name,frament1.start_index,frament1.end_index,
                        frament_seq1.error_count,frament_seq1.snp_count,frament_seq1.indel_count,
                        id,frament1.reverse);

                writer0->WriteRead(frament_seq0.sequence);
                writer1->WriteRead(frament_seq1.sequence);

                writer0->EndRead();
                writer1->EndRead();
            }
        }
    }
}
