#ifndef __GENOMESEQUENCE_SEQUENCE_H__
#define __GENOMESEQUENCE_SEQUENCE_H__

#include <string>
#include <vector>

namespace GSS
{
    std::string GetRandomFragment(const std::string & base , int len , bool reverse );
    std::string Head(const std::string & base , int len);
    std::string Tail(const std::string & base , int len);
    std::string GenomeReverse(const std::string & base);

    void TestInterface();

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

        private:
            static inline int CHAR2ID(char c) 
            {
                return c & 0x6 ;
            }

        public:
            static inline char ID2CHAR(int id) 
            {
                return "ATGC"[id];
            }
        public:
            inline bool IsDelete() const { return DEL ;}
            inline bool IsSNP() const { return SNP != ID;}
            inline bool IsInsert() const { return IN_NUM > 0 ;}
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
                ID = CHAR2ID(c);
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
            GenomeSequenece(const std::string & sequence);
            void Polymorphic(double mut_rate, double indel_factor,double indel_extern) ;
            std::string GetRandomFragment(int len , bool reverse);

            //void CleanSequence();
        private:
            bool dirty ;
            std::vector<DNA_Bit> sequence;
    };
}

#endif //__GENOMESEQUENCE_SEQUENCE_H__
