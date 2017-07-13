#ifndef __GENOMESEQUENCE_LOGIC_H__
#define __GENOMESEQUENCE_LOGIC_H__

#include <vector>
#include "config.h"
#include "iFileWR.h"
#include <memory>
#include "sequence.h"

namespace GSS
{
    struct OutputLogic;

    class Logic
    {
        public:
            static std::unique_ptr<Utils::IFileReader>  GetFileReader(const Config & conf) ;
            static std::unique_ptr<Utils::IFileWriter>  GetFileWriter(const GSS::GenomeSequenceInfo::FileType t , const std::string & filename) ;
    };

    struct OutputLogic
    {
        private:
            const GenomeSequenceInfo & info;

            std::unique_ptr<Utils::IFileWriter> writer0;
            std::unique_ptr<Utils::IFileWriter> writer1;

            OutputLogic(const OutputLogic & ) ;
            OutputLogic & operator=(const OutputLogic & ) ;
        public:
            OutputLogic(const GenomeSequenceInfo & i)
                :info(i)
            {
                if(i.read_type == GenomeSequenceInfo::ReadType::SINGLE)
                {
                    writer0 = Logic::GetFileWriter(i.file_type,i.file_name);
                }
                else
                {
                    writer0 = Logic::GetFileWriter(i.file_type,i.file_name+"_0");
                    writer1 = Logic::GetFileWriter(i.file_type,i.file_name+"_1");
                }
            }
            void Process1Sequence(const GenomeSequenece & sequence, double error_rate);
    };


}// namespace GSS
#endif //__GENOMESEQUENCE_LOGIC_H__
