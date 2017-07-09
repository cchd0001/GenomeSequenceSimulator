#ifndef __UTILS_LOG_UTILSERROR_HPP__
#define __UTILS_LOG_UTILSERROR_HPP__

#include <stdarg.h>

namespace Utils// Classes and interfaces that any kind of project can use .
{
    void QuitWithErrno(const char *, va_list );
    void QuitWithoutErrno(const char *, va_list);
    void WarningWithErrno(const char *, va_list);
    void WarningWithoutErrno(const char *,va_list);

    inline void FATAL_TRUE( bool args , const char * fmt="" , ...) 
    {
        if(!args)
        {
           va_list others;
           va_start(others,fmt);
           QuitWithoutErrno(fmt,others);
           va_end(others);
        }
        return;
    }

    inline void FATAL_TRUE_EN( bool args , const char * fmt="" , ...) 
    {
        if(!args)
        {
           va_list others;
           va_start(others,fmt);
           QuitWithErrno(fmt,others);
           va_end(others);
        }
        return;
    }

    inline void FATAL_FALSE_EN(bool args , const char * fmt="" , ...)
    {
        if(args)
        {
           va_list others;
           va_start(others,fmt);
           QuitWithErrno(fmt,others);
           va_end(others);
        }
        return;
    }

    inline void FATAL_FALSE(bool args , const char * fmt="" , ...)
    {
        if(args)
        {
           va_list others;
           va_start(others,fmt);
           QuitWithoutErrno(fmt,others);
           va_end(others);
        }
        return;
    }


    inline void CHECK_TRUE( bool args , const char * fmt="" , ...) 
    {
        if(!args)
        {
           va_list others;
           va_start(others,fmt);
           WarningWithoutErrno(fmt,others);
           va_end(others);
        }
        return;
    }

    inline void CHECK_TRUE_EN( bool args , const char * fmt="" , ...) 
    {
        if(!args)
        {
           va_list others;
           va_start(others,fmt);
           WarningWithErrno(fmt,others);
           va_end(others);
        }
        return;
    }

    inline void CHECK_FALSE_EN(bool args , const char * fmt="" , ...)
    {
        if(args)
        {
           va_list others;
           va_start(others,fmt);
           WarningWithErrno(fmt,others);
           va_end(others);
        }
        return;
    }

    inline void CHECK_FALSE(bool args , const char * fmt="" , ...)
    {
        if(args)
        {
           va_list others;
           va_start(others,fmt);
           WarningWithoutErrno(fmt,others);
           va_end(others);
        }
        return;
    }

} // namespace Utils

#endif //__UTILS_LOG_UTILSERROR_HPP__
