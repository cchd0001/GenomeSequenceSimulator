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

    Config::Instance().InitFromJson("config.json");
    CHECKPOINT(Load config pass ... );

    auto reader = Logic::GetFileReader(Config::Instance());
    std::string genome(reader->GetNextRead());

    GenomeSequenece sequence(genome);

    std::cout<<"Toatl genome size "<<genome.length()<<std::endl;
    CHECKPOINT(Load refrence genome pass ... );

    auto fill_one_output =  [ &] (const  GenomeSequenceInfo & info) {
        unsigned long long id  = 0;
        unsigned long long maxId = (unsigned long long) genome.length()/info.read_length * info.depth;
        std::string commond = "Simulator data , type " 
            + (info.read_type == GenomeSequenceInfo::SINGLE ? std::string("Single") : std::string("Pair-End"))
            + " insert_len " + std::to_string(info.insert_length) 
            + " read_len " + std::to_string(info.read_length)
            + " id ";

        if( info.read_type == GenomeSequenceInfo::PAIR_END)
        {

            auto  writer0 = Logic::GetFileWriter(info.file_type, info.file_name+"_0");
            auto  writer1 = Logic::GetFileWriter(info.file_type, info.file_name+"_1");
            while( id < maxId)
            {
                writer0->StartNewRead(commond + std::to_string(id));
                writer1->StartNewRead(commond + std::to_string(id));
                //std::string base = GetRandomFragment(genome,info.insert_length, rand()&0x1);
                //writer0->WriteRead(Head(base,info.read_length));
                //writer1->WriteRead(Tail(base,info.read_length));
                auto base = sequence.GetRandomFragment(info.insert_length,rand() & 0x1);
                writer0->WriteRead(sequence.GetFramentSequence(base.Head(info.read_length)));
                writer1->WriteRead(sequence.GetFramentSequence(base.Tail(info.read_length)));
                writer0->EndRead();
                writer1->EndRead();
                id++;
            }
        }
        else
        {
            auto  writer = Logic::GetFileWriter(info.file_type, info.file_name);
            while( id < maxId)
            {
                writer->StartNewRead(commond + std::to_string(id));
                //writer->WriteRead(GetRandomFragment(genome, info.read_length,rand() & 0x1));
                writer->WriteRead(sequence.GetFramentSequence(sequence.GetRandomFragment(info.insert_length,rand() & 0x1)));
                writer->EndRead();
                id ++;
            }
        }
        CHECKPOINT(Generator a output data ... );
    };
    Config::Instance().ForEachInfo(fill_one_output);
    TASK_END;
    return 0;
}
