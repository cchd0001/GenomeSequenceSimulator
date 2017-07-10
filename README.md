# GenomeSequenceSimulator
A simulator to genarate WSG data for Genome denovo 

*INSTALL

Simple build by cmake .

Here is a build example.
Enter src directory:
```
    mkdir build
    cd build
    cmake ..
    make
```

Binary execute file in bin/Bin/GSS

*EXAMPLE
After build success ,enter example directory and run ```example.sh``` script.


*QUICK START

Run GSS with config.json file . All infomations are within config.json. 

Here is part of config.json from example
```
{                                       #Top level is a object !
    "filePath": "./sequence.fasta",     #Basic genome file. 
    "fileType": "fasta",                #Genome file type.Only support fasta now.
    "output": [                         #Array of all simulator infos.
        {
            "file_name":"f0",           #Output name prefix.
            "file_type":"fastq",        #Output file type,support fasta and fastq
            "read_type": "single",      #
            "read_len": 100,            #
            "insert_len": 100,          #
            "depth":80                  #The expect depth of Nucleotide.
        },
        {
            "file_name":"f1",
            "file_type":"fastq",
            "read_type": "pair-end",
            "read_len": 100,
            "depth":100,
            "insert_len": 250
        }
    ]
}
```





