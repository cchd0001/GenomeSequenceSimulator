#ifndef __UTILS_IFILEWR_IFILEWR_H__
#define __UTILS_IFILEWR_IFILEWR_H__

#include <string>
namespace Utils
{

struct ReadInfo
{
    std::string name;
    std::string comment;
    std::string read;
    std::string quality;
};

class IFileReader
{

    public:

        virtual const ReadInfo GetNextRead()=0 ;

        virtual bool Eof() const = 0;

        virtual ~IFileReader() {}
};

class IFileWriter
{
    public:

        virtual void StartNewRead(const std::string & name,int start,int end ,
                                  int error_count,int snp_count,int indel_count,
                                  int index ,bool reverse) = 0;

        virtual void WriteRead(const std::string & read) = 0;

        virtual void EndRead() = 0;

        virtual ~IFileWriter(){}
};

}//namespace Utils
#endif //__UTILS_IFILEWR_IFILEWR_H__
