#ifndef __UTILS_TIMELOG_H__
#define __UTILS_TIMELOG_H__

#include <time.h>
#include <string>
#include <iostream>

namespace Utils
{

    class TimeLog
    {
        public:
            TimeLog(const std::string& tname) 
                :task_name(tname)
            {
                time(&begin);
                last_checkpoint = begin;
                std::cout<<"Task -- "<<tname<<" start ... "<<std::endl;
            }

            void Checkpoint(const std::string & cname)
            {
                time_t prev = last_checkpoint;
                time(&last_checkpoint);
                std::cout<<"Checkpoint -- "<<cname<<" finish. Last phase used "<<last_checkpoint-prev<<" seconds."<<std::endl;
            }
            ~TimeLog()
            {
                std::cout<<"Task "<<task_name<<" end with "<<time(0)-begin<<" seconds used."<<std::endl;
            }

        private:
            std::string task_name;
            time_t begin;
            time_t last_checkpoint;
    };


#define TASK_BEGIN(name) \
        Utils::TimeLog * curr_tlog = new Utils::TimeLog(#name)

#define CHECKPOINT(name) \
        if(curr_tlog) curr_tlog->Checkpoint(#name)

#define TASK_END \
        if(curr_tlog) delete curr_tlog

}//namespace Utils


#endif //__UTILS_TIMELOG_H__
