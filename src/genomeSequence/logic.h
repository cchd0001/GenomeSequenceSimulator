#ifndef __GENOMESEQUENCE_LOGIC_H__
#define __GENOMESEQUENCE_LOGIC_H__

#include <vector>
#include "config.h"
#include "iFileWR.h"
#include <memory>

namespace GSS
{

    class Logic
    {
        public:
            static std::unique_ptr<Utils::IFileReader>  GetFileReader(const Config & conf) ;
            static std::unique_ptr<Utils::IFileWriter>  GetFileWriter(const GSS::GenomeSequenceInfo::FileType t , const std::string & filename) ;
    };


}// namespace GSS
#endif //__GENOMESEQUENCE_LOGIC_H__
