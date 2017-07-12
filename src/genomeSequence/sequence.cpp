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
        FATAL_TRUE(DNA_Bit::CHAR2ID('A') == 0);
        FATAL_TRUE(DNA_Bit::CHAR2ID('C') == 1);
        FATAL_TRUE(DNA_Bit::CHAR2ID('T') == 2);
        FATAL_TRUE(DNA_Bit::CHAR2ID('G') == 3);
        FATAL_TRUE(DNA_Bit::ID2CHAR(0) == 'A');
        FATAL_TRUE(DNA_Bit::ID2CHAR(1) == 'C');
        FATAL_TRUE(DNA_Bit::ID2CHAR(2) == 'T');
        FATAL_TRUE(DNA_Bit::ID2CHAR(3) == 'G');
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

    GenomeSequenece::GenomeFragment GenomeSequenece::GetRandomFragment(int len , bool reverse)
    {
        GenomeFragment ret;
        ret.start_index = rand() % ( sequence.size()- len );
        ret.end_index = ret.start_index + len ;
        ret.reverse = reverse;
        return ret;
    }


    std::string  GenomeSequenece::GetFramentSequence(const GenomeSequenece::GenomeFragment & frament)
    {
        std::string ret(frament.end_index-frament.start_index,'N');
        int index = 0;
        auto setSeq=[&index,&ret](const DNA_Bit & dna_bit)
        {
            if(dna_bit.NoChange())
            {
                ret.at(index++) =DNA_Bit::ID2CHAR( dna_bit.Id());
            }
            else
            {
                if(dna_bit.IsDelete())
                {
                    return ;
                }
                if(dna_bit.IsSNP())
                {
                    ret.at(index++) = DNA_Bit::ID2CHAR(dna_bit.SNPId());
                    return ;
                }
                if(dna_bit.IsInsert())
                {
                    for(int j= 0 ; j < dna_bit.InsertNum(); j++)
                    {
                        ret.at(index++) = dna_bit.InsertID(j);
                    }
                }
            }
        };
        if(!frament.reverse)
        {
            for(int i = frament.start_index; i < frament.end_index &&index < (int)ret.length(); i++)
            {
                setSeq( sequence.at(i));
            }
        }
        else
        {
            for(int i = frament.end_index -1 ; i >= frament.start_index &&index < (int)ret.length(); i--)
            {
                setSeq( sequence.at(i));
            }
        }
        return ret;
    }

}//namespace GSS
