
set(fastqDir  ${utilsDir}/fastq)

include_directories(${fastqDir})

set(source_h ${source_h} ${fastqDir}/fastQ.h)
set(source_cpp ${source_cpp}  ${fastqDir}/fastQ.cpp)
