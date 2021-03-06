#include "config.h"
#include <iostream>
#include "fastQ.h"
#include "fastA.h"
#include "sequence.h"
#include "logic.h"
#include <stdlib.h>
#include "timeLog.h"

using namespace GSS;
using namespace Utils;

int main()
{
    TASK_BEGIN(GenomeSequenceSimulator);

    TestInterface();
    std::cout<<"Test pass ..."<<std::endl;
    srand(time(0));
    std::srand(time(0));

    std::cout<<"Init random seed pass ..."<<std::endl;
    Config & conf = Config::Instance();
    conf.InitFromJson("config.json");
    auto reader = Logic::GetFileReader(conf);
    OutputLogic ** OLogics = new OutputLogic *[conf.OutputSize()];

    int itr = 0;
    auto fill_one_output =  [&itr, &OLogics] (const  GenomeSequenceInfo & info) {
        *(OLogics + itr++) = new OutputLogic(info);

    };
    conf.ForEachInfo( fill_one_output );
    CHECKPOINT(Load config pass ... );


    while(!reader->Eof())
    {
        auto rInfo = reader->GetNextRead();
        std::cout<<"--------------------------------------------------------------"<<std::endl;
        std::cout<<"Load a new sequence now ..."<<std::endl;
        std::cout<<"Genome name    "<<rInfo.name<<std::endl;
        std::cout<<"Genome comment "<<rInfo.comment<<std::endl;
        std::cout<<"Genome size    "<<rInfo.read.size()<<std::endl;
        std::cout<<"--------------------------------------------------------------"<<std::endl;
        GenomeSequenece sequence(rInfo.name, rInfo.read);
        sequence.Polymorphic(conf.variation_rate,conf.indel_rate,conf.indel_extern);
        std::cout<<"--------------------------------------------------------------"<<std::endl;
        for( int i = 0 ; i < (int)conf.OutputSize() ; i++ )
        {
            (*(OLogics+i))->Process1Sequence(sequence,conf.error_rate);
            CHECKPOINT(write a ouput by curr reference end);
        }
    }

    for( int i = 0 ; i < (int)conf.OutputSize() ; i++ )
    {
        delete (*(OLogics+i));
    }
    delete []OLogics;

    TASK_END;
    return 0;
}
