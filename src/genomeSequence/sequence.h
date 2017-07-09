#ifndef __GENOMESEQUENCE_SEQUENCE_H__
#define __GENOMESEQUENCE_SEQUENCE_H__

#include <string>

namespace GSS
{
    std::string GetRandomFragment(const std::string & base , int len , bool reverse );
    std::string Head(const std::string & base , int len);
    std::string Tail(const std::string & base , int len);
}

#endif //__GENOMESEQUENCE_SEQUENCE_H__
