set(logDir ${utilsDir}/log)

include_directories(${logDir})
set(source_cpp ${source_cpp} ${logDir}/utilsError.cpp)
set(source_h ${source_cpp} ${logDir}/utilsError.hpp)

