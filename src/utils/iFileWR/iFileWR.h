#ifndef __UTILS_IFILEWR_IFILEWR_H__
#define __UTILS_IFILEWR_IFILEWR_H__

#include <string>
namespace Utils
{
class IFileReader
{

    public:
        virtual const std::string  GetNextRead()=0 ;

        virtual bool Eof() const = 0;
};

class IFileWriter
{
    public:

        virtual void StartNewRead(const std::string & comment) = 0;

        virtual void WriteRead(const std::string & read) = 0;

        virtual void EndRead() = 0;
};

}//namespace Utils
#endif //__UTILS_IFILEWR_IFILEWR_H__
