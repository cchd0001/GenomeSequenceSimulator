set(utilsDir ${PROJECT_SOURCE_DIR}/utils)

include_directories(${utilsDir}/iFileWR)

include(${utilsDir}/log/CMakeLists.txt)
include(${utilsDir}/fastq/CMakeLists.txt)
include(${utilsDir}/fasta/CMakeLists.txt)
