#include "sequence.h"
#include "utilsError.hpp"
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace Utils;
namespace GSS
{
    void TestInterface()
    {
        FATAL_TRUE(DNA_Bit::CHAR2ID('A') == 0);
        FATAL_TRUE(DNA_Bit::CHAR2ID('C') == 1);
        FATAL_TRUE(DNA_Bit::CHAR2ID('T') == 2);
        FATAL_TRUE(DNA_Bit::CHAR2ID('G') == 3);
        FATAL_TRUE(DNA_Bit::ID2CHAR(0) == 'A');
        FATAL_TRUE(DNA_Bit::ID2CHAR(1) == 'C');
        FATAL_TRUE(DNA_Bit::ID2CHAR(2) == 'T');
        FATAL_TRUE(DNA_Bit::ID2CHAR(3) == 'G');

    }


    GenomeSequenece::GenomeSequenece(const std::string & n ,const std::string &seq): dirty(false) , name(n),sequence(seq.length())
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

        auto polymorphic_1bit = [&](DNA_Bit & dna_bit)
        {
            if(delete_flag && drand48() < indel_extern)
            {
                dna_bit.DoDelete();
                return ;
            }
            else
            {
                delete_flag = false;
            }

            if(drand48() > mut_rate)
            {
                return ;
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

        };

        int last_delete = -1;
        auto print_polymorphic_1bit = [&](DNA_Bit & dna_bit,int index)
        {
            std::cout<<name<<"\t"<<index<<"\t";
            if(dna_bit.IsDelete())
            {
                for(int deleteId = index ; sequence.at(deleteId).IsDelete(); deleteId++)
                {
                    std::cout<<DNA_Bit::ID2CHAR(sequence.at(deleteId).Id());
                    last_delete = deleteId;
                }
                std::cout<<"\t-\t-"<<"#DEL "<<index<<"-"<<last_delete<<std::endl;
                return ;
            }
            if(dna_bit.IsSNP())
            {
                std::cout<<DNA_Bit::ID2CHAR(dna_bit.Id())<<"\t"
                         <<DNA_Bit::ID2CHAR(dna_bit.SNPId())<<"\t-"
                         <<"#SNP "<<dna_bit.Id()<<" -> "<<dna_bit.SNPId()<<std::endl;
                return;
            }
            if(dna_bit.IsInsert())
            {
                std::cout<<DNA_Bit::ID2CHAR(dna_bit.Id())<<"\t";
                for(int i = 0 ; i< dna_bit.InsertNum(); i++)
                {
                    std::cout<<DNA_Bit::ID2CHAR(dna_bit.InsertID(i));
                }
                std::cout<<"\t-"<<"#Insert" <<dna_bit.InsertNum()<<std::endl;
                return ;
            }
        };

        for(size_t i = 0; i< sequence.size() ; i++) 
        {
            polymorphic_1bit(sequence.at(i));
        }
        for(size_t i = 0; i< sequence.size() ; i++) 
        {
            if(sequence.at(i).NoChange() || (int)i <= last_delete )
            {
                continue;
            }
            print_polymorphic_1bit(sequence.at(i),i);
        }
    }

    GenomeSequenece::GenomeFragment GenomeSequenece::GetRandomFragment(int len , bool reverse) const
    {
        GenomeFragment ret;
        ret.start_index = rand() % ( sequence.size()- len );
        ret.end_index = ret.start_index + len ;
        ret.reverse = reverse;
        return ret;
    }

    std::string  GenomeSequenece::GetFramentSequence(const GenomeSequenece::GenomeFragment & frament,double unccorrect) const
    {
        std::string ret(frament.end_index-frament.start_index,'N');
        int index = 0;
        auto setSeq=[&index,&ret,&unccorrect](const DNA_Bit & dna_bit, int len)
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
                    for(int j= 0 ; j < dna_bit.InsertNum() && index < len; j++)
                    {
                        ret.at(index++) = DNA_Bit::ID2CHAR(dna_bit.InsertID(j));
                    }
                }
            }

            if(drand48() < unccorrect)
            {
                 ret.at(index-1) = DNA_Bit::ID2CHAR(
                         (DNA_Bit::CHAR2ID(ret.at(index-1)) + 1) & 0x3);
            }
        };
        if(!frament.reverse)
        {
            for(int i = frament.start_index; i < frament.end_index &&index < (int)ret.length(); i++)
            {
                setSeq( sequence.at(i),ret.length());
            }
        }
        else
        {
            for(int i = frament.end_index -1 ; i >= frament.start_index &&index < (int)ret.length(); i--)
            {
                setSeq( sequence.at(i),ret.length());
            }
        }
        return ret;
    }

}//namespace GSS
