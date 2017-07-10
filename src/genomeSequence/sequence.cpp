#include "sequence.h"
#include "utilsError.hpp"
#include <stdlib.h>
#include <algorithm>
using namespace Utils;
namespace GSS
{

    std::string GenomeReverse(const std::string & base)
    {
        std::string ret(base.length(),'N');
        int i = 0 ;
        for(auto it = base.rbegin(); it != base.rend() ; i++,it = std::next(it))
        {
            ret[i] = *it == 'A' ? 'T' : *it == 'T' ? 'A' : *it =='G' ? 'C' : 'G';
        }
        return ret;
    }

    std::string GetRandomFragment(const std::string & base , int len , bool r)
    {
        FATAL_TRUE(base.length() > (size_t)len);
        int start = rand() % (base.length() - len );
        std::string ret = base.substr(start,len);
        if(r)
        {
            ret = GenomeReverse(ret);
        }
        return ret;
    }

    std::string Head(const std::string & base , int len )
    {
        FATAL_TRUE(base.length() > (size_t)len);
        return base.substr(0,len);
    }

    std::string Tail(const std::string & base ,int len)
    {
        FATAL_TRUE(base.length() > (size_t)len);
        std::string ret = base.substr(base.length() - len);
        ret = GenomeReverse(ret);
        return ret;
    }

}//namespace GSS
