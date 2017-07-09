
set(genomeSequenceDir ${PROJECT_SOURCE_DIR}/genomeSequence)

include_directories(${genomeSequenceDir})

set(source_h ${source_h} ${genomeSequenceDir}/sequence.h)
set(source_cpp ${source_cpp} ${genomeSequenceDir}/sequence.cpp)
