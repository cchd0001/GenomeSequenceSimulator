set(fastaDir  ${utilsDir}/fasta)

include_directories(${fastaDir})

set(source_h ${source_h} ${fastaDir}/fastA.h)
set(source_cpp ${source_cpp}  ${fastaDir}/fastA.cpp)
