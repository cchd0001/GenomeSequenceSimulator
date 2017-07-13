#ifndef __GENOMESEQUENCE_SEQUENCE_H__
#define __GENOMESEQUENCE_SEQUENCE_H__

#include <string>
#include <vector>
#include <map>

namespace GSS
{

    struct DNA_Bit
    {
        private:
            int IN_ID:8;
            int IN_NUM:3;
            int DEL:1;
            int SNP:2;
            int ID:2;

        public:
            DNA_Bit() : IN_ID(0) , IN_NUM(0), DEL(0), SNP(0),ID(0) {}

            static inline int CHAR2ID(char c) 
            {
                //return (c & 0x6 )>>1; // 0000 0110
                switch(c)
                {
                    case 'A':
                        return 0;
                    case 'C':
                        return 1;
                    case 'T':
                        return 2;
                    case 'G':
                        return 3;
                }
                return 'G';
            }

        public:
            static inline char ID2CHAR(int id) 
            {
                return "ACTG"[id];
            }
        public:
            inline bool IsDelete() const { return DEL ;}
            inline bool IsSNP() const { return SNP != ID;}
            inline bool IsInsert() const { return IN_NUM > 0 ;}
            inline bool NoChange() const { return !IN_NUM && !DEL && SNP == ID ; }
            inline int  Id() const { return ID & 0x3 ; }
            inline int  SNPId() const { return SNP & 0x3; }

        public:
            inline int  InsertNum() const { return IN_NUM ; }
            inline char InsertID(int i) const 
            {
                return  ID2CHAR(IN_ID&(0x3 <<i)) ;
            }
        public:
            inline void DoDelete() { DEL = 1; }
            inline void DoSNP()
            {
                do
                {
                    SNP = rand() % 4;
                }while(SNP != ID);
            }
            inline void DoInsert(float indel_extern)
            {
                do
                {
                    IncrInsert();
                    SetCurrInsertChar("ATGC"[rand() & 0x3]);
                }while(IN_NUM < 5 && drand48() <indel_extern);
            }

        public:
            inline void SetChar(char c)
            {
                ID = CHAR2ID(c) & 0x3;
                SNP= ID ;
            }
        private:
            inline void IncrInsert() { IN_NUM ++ ; }
            inline void SetSNP(char c) 
            {
                SNP = CHAR2ID(c);
            }
            inline void SetCurrInsertChar(char c) 
            {
                IN_ID |= CHAR2ID(c) << (2*(IN_NUM -1));
            }
    };

    class GenomeSequenece
    {
        public:
            struct GenomeFragment
            {
                // [start_index,end_index) ==>
                // [start_index,end_index) <==
                int start_index;
                int end_index;
                bool reverse;
                inline GenomeFragment Head(int len)
                {
                    GenomeFragment ret = *this;
                    if(!reverse)
                    {
                        ret.end_index = ret.start_index + len ;
                    }
                    else
                    {
                        ret.start_index = ret.end_index - len;
                    }
                    return ret;
                }
                inline GenomeFragment Tail(int len)
                {
                    GenomeFragment ret = *this;;
                    if(!reverse)
                    {
                        ret.start_index = end_index - len ;
                    }
                    else
                    {
                        ret.end_index = start_index + len;
                    }
                    ret.reverse = !reverse ;
                    return ret;
                }
            };
            GenomeSequenece(const std::string & sequence);
            void Polymorphic(double mut_rate, double indel_factor,double indel_extern) ;
            GenomeFragment GetRandomFragment(int len , bool reverse) const;
            std::string GetFramentSequence(const GenomeFragment & frament) const;
            size_t length()const {return  sequence.size(); }
        private:
            bool dirty ;
            std::vector<DNA_Bit> sequence;
    };//class GenomeSequence

    void TestInterface();
}

#endif //__GENOMESEQUENCE_SEQUENCE_H__
