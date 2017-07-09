#include "utilsError.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

extern int errno;

namespace Utils{

#define MAXNERROR 1024
    static const char *test_format(const char * format)
    {
        static char default_format[] = "check error without useful message!";
        if(format && strlen(format) > 0)
            return format;
        else 
            return default_format;

    }
    static void err_print(const char * format,va_list va )
    {
        char error_buff[MAXNERROR];
        vsnprintf(error_buff, MAXNERROR, format, va);
        snprintf(error_buff+strlen(error_buff),MAXNERROR -strlen(error_buff), " : %s .\n",strerror(errno));
        fprintf(stderr,"%s",error_buff);
        va_end(va);
    }

    void QuitWithErrno(const char *format, va_list va)
    {
        const char * str = test_format(format);
        err_print(str,va);
        exit(0);
    }

    void QuitWithoutErrno(const char * format, va_list va)
    {
        const char * str = test_format(format);
        char error_buff[MAXNERROR];
        vsnprintf(error_buff, MAXNERROR , str ,va );
        va_end(va);
        fprintf(stderr,"%s\n",error_buff);
        exit(0);
    }
    void WarningWithErrno(const char *format, va_list va)
    {
        const char * str = test_format(format);
        err_print(str,va);
        return ;
    }
    void WarningWithoutErrno(const char *format,va_list va) 
    {
        const char * str = test_format(format);
        char error_buff[MAXNERROR];
        vsnprintf(error_buff, MAXNERROR , str ,va );
        va_end(va);
        fprintf(stderr,"%s\n",error_buff);
        return;
    }
}
