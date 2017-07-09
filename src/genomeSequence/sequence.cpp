#include "sequence.h"
#include "utilsError.hpp"
#include <stdlib.h>
#include <algorithm>
using namespace Utils;
namespace GSS
{
    std::string GetRandomFragment(const std::string & base , int len , bool r)
    {
        FATAL_TRUE(base.length() > (size_t)len);
        int start = rand() % (base.length() - len );
        std::string ret = base.substr(start,len);
        if(r)
        {
            std::reverse(ret.begin() , ret.end());
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
        std::reverse(ret.begin(),ret.end());
        return ret;
    }

}//namespace GSS
