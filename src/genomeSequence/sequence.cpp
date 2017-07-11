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
        FATAL_TRUE(base.length() > (size_t)len , "insert_len greater than genome size" );
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
        FATAL_TRUE(base.length() > (size_t)len , "read_len greater than insert_len");
        return base.substr(0,len);
    }

    std::string Tail(const std::string & base ,int len)
    {
        FATAL_TRUE(base.length() > (size_t)len,"read_len greater than insert_len");
        std::string ret = base.substr(base.length() - len);
        ret = GenomeReverse(ret);
        return ret;
    }

    void TestInterface()
    {
        FATAL_TRUE("ATGCCCATG" == GenomeReverse("CATGGGCAT"), "GenomeReverse error");
        FATAL_TRUE("ATGC" == Head("ATGCASDASDASD",4) , "Head error");
        FATAL_TRUE("ATGC" == Tail("ARFSFGSDAGCAT",4), "Tail error");
    }


    GenomeSequenece::GenomeSequenece(const std::string &seq): dirty(false) , sequence(seq.length())
    {
        int i = 0;
        for( auto it = seq.begin(); it != seq.end() ; it = std::next(it), i++)
        {
            sequence.at(i).SetChar(*it);
        }
    }

    void GenomeSequenece::Polymorphic(double mut_rate, double indel_factor,double indel_extern)
    {
        if(dirty) 
        {
            return ;
        }
        dirty = true;
        bool delete_flag = false;
        for(auto  it = sequence.begin() ; it != sequence.end() ; it = std::next(it)) 
        {
            DNA_Bit & dna_bit = *it;
            if(delete_flag && drand48() < indel_extern)
            {
                dna_bit.DoDelete();
                continue;
            }
            else
            {
                delete_flag = false;
            }

            if(drand48() > mut_rate)
            {
                continue;
            }
            if(drand48() > indel_factor)
            {
                dna_bit.DoSNP();
            }
            else
            {
                if(drand48() > 0.05f)
                {
                    dna_bit.DoDelete();
                    delete_flag = true;
                }
                else
                {
                    dna_bit.DoInsert(indel_extern);
                }
            }
        }
    }

}//namespace GSS
