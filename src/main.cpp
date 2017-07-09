#include "config.h"
#include <iostream>
#include "fastQ.h"
#include "fastA.h"
#include "sequence.h"

using namespace GSS;
using namespace Utils;
int main()
{
    Config::Instance().InitFromJson("config.json");
    FastAReader reader(Config::Instance().SourceFile());
    std::string genome(reader.GetNextRead());
    std::cout<<"Toatl genome size "<<genome.length()<<std::endl;

    int index = 0 ;
    Config::Instance().ForEachInfo( [ &] (const  GenomeSequenceInfo & info) {
        std::cout<<"Work for info "<< index++<<std::endl;
        unsigned long long id  = 0;
        unsigned long long maxId = ((unsigned long long) genome.length() / info.read_length) * info.depth;
        std::string commond = "Simulator data , type " 
                 + (info.read_type == GenomeSequenceInfo::SINGLE ? std::string("Single") : std::string("Pair-End"))
                 + " insert_len " + std::to_string(info.insert_length) 
                 + " read_len " + std::to_string(info.read_length)
                 + " id ";
        if( info.read_type == GenomeSequenceInfo::PAIR_END)
        {

            FastQWriter writer0(info.file_name+"_0");
            FastQWriter writer1(info.file_name+"_1");
            while( id < maxId)
            {
                 writer0.StartNewRead(commond + std::to_string(id));
                 writer1.StartNewRead(commond + std::to_string(id));
                 std::string base = GetRandomFragment(genome,info.insert_length, rand()&0x1);
                 writer0.WriteRead(Head(base,info.read_length));
                 writer1.WriteRead(Tail(base,info.read_length));
                 writer0.EndRead();
                 writer1.EndRead();
                 id++;
            }
        }
        else
        {
            FastQWriter writer(info.file_name);
            while( id < maxId)
            {
                 writer.StartNewRead(commond + std::to_string(id));
                writer.WriteRead(GetRandomFragment(genome, info.read_length,rand() & 0x1));
                 writer.EndRead();
                id ++;
            }
        }
   });

    return 0;
}
