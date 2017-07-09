#include "config.h"
#include <cassert>
#include "rapidjson/document.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "utilsError.hpp"
#include "rapidjson/prettywriter.h" 

using namespace Utils;

namespace GSS
{

Config & Config::Instance()
{
    static Config s_instance;
    return s_instance;
}

void Config::ForEachInfo(std::function<void(const GenomeSequenceInfo&)>f ) const 
{
    for(const GenomeSequenceInfo & i : infos)
    {
        f(i);
    }
}

#define CHECK_JSON_ITEM(map,name,type) \
    CHECK_TRUE(map.HasMember(#name) && map[#name].Is##type(),"Item %s check failed!",#name)

static rapidjson::Value::MemberIterator tmp;
 #define JSON_STRING(map, name) \
    ( (tmp = map.FindMember(#name)) , tmp->value.GetString())

static const std::string fasta("fasta");
static const std::string fastq("fastq");
static const std::string single("single");
static const std::string pair_end("pair-end");


void Config::InitFromJson( const std::string &json_file)
{
    std::ifstream ifs ;
    ifs.open(json_file,std::ios::in);

    FATAL_TRUE_EN(ifs.is_open(),"ERROR -- open file %s failed ! ", json_file.c_str());
    rapidjson::Document doc;
    std::stringstream buffer;
    buffer<<ifs.rdbuf();
    FATAL_FALSE(doc.Parse<0>(buffer.str().c_str()).HasParseError(),\
        "ERROR -- Config file %s has parse error !!", json_file.c_str());

    CHECK_JSON_ITEM(doc,fileType,String);
    CHECK_JSON_ITEM(doc,filePath,String);
    CHECK_JSON_ITEM(doc,output,Array);

    source_file = JSON_STRING(doc,filePath);

    if( JSON_STRING(doc,fileType) ==fastq )
    {
        input_file_type = FASTQ;
    }
    else
    {
        FATAL_TRUE(false, "Only support %s input now . ",fastq.c_str());
    }
    const rapidjson::Value& a = doc["output"];
    for (rapidjson::SizeType i = 0; i < a.Size(); i++)
    {
        const rapidjson::Value & a_output =  a[i];
        CHECK_JSON_ITEM(a_output,file_type,String);
        CHECK_JSON_ITEM(a_output,read_type,String);
        CHECK_JSON_ITEM(a_output,read_len,Int);
        CHECK_JSON_ITEM(a_output,insert_len,Int);
        CHECK_JSON_ITEM(a_output,depth,Int);
        CHECK_JSON_ITEM(a_output,file_name,String);

        GenomeSequenceInfo a_info;

        a_info.file_name = a_output["file_name"].GetString();
        /*if( a_output["file_type"].GetString() == fasta ) 
        {
            a_info.file_type = GenomeSequenceInfo::FASTA;
        }
        else*/ if ( a_output["file_type"].GetString() == fastq )
        {
            a_info.file_type = GenomeSequenceInfo::FASTQ;
        }
        else
        {
            FATAL_TRUE(false , "output file_type only support %s !",fastq.c_str());
        }

        if( a_output["read_type"].GetString() == single) 
        {
            a_info.read_type= GenomeSequenceInfo::SINGLE;
        }
        else if ( a_output["read_type"].GetString() == pair_end)
        {
            a_info.read_type= GenomeSequenceInfo::PAIR_END;
        }
        else
        {
            FATAL_TRUE(false , "output read_type only support %s  && %s !",single.c_str(),pair_end.c_str());
        }

        a_info.read_length = a_output["read_len"].GetInt();
        a_info.insert_length = a_output["insert_len"].GetInt();
        a_info.depth = a_output["depth"].GetInt();

        infos.push_back(a_info);
    }

    std::cout<<"Total output item "<<infos.size()<<std::endl;
}


}//namespace GSS
