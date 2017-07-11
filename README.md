# GenomeSequenceSimulator

A small tool for simulating sequence reads from a reference genome

* INSTALL

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

* EXAMPLE

After build success ,enter example directory and run ```example.sh``` script.


* QUICK START

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
* OUTPUT 

Here is the top 10 lines of each file that generator by above config.json

```
==> f0.fastq <==
@Simulator data , type Single insert_len 100 read_len 100 id 0
CTTTATCACGAAATGATAGATTCAGGCGTTATTAAGCCAGAAGGTCCAGGATCAAAAGCTGCATTAGTGTATGGTCAAATGAATGAACCCCCAGGAGCTA
+
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
@Simulator data , type Single insert_len 100 read_len 100 id 1
ATCCTAATTCAAATCTCACTTGATCATTTCCTTTGCCAGTTGAACCATGAGAAACTGCATAAGCTCCAAATTTTTTAGCGGCAGCAATTTGACGTTTTGC
+
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
@Simulator data , type Single insert_len 100 read_len 100 id 2
ACTATATTTTCTAGCGATACAATGAATAAAAAAAGTTCAGCAGATGTTTTAGAAAAAATTATAGATAATAAAATTCAAATTTTAATTGGAACTCAATTAA

==> f1_0.fastq <==
@Simulator data , type Pair-End insert_len 250 read_len 100 id 0
CAATAGATAATTCAGGAGATAGAACTAAGGCAAATTTTTTAACTGAGATGATAGTAGAAGACGTCATTGGAAGTAAAAATTCTTTCTATGGAGTAAATTC
+
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
@Simulator data , type Pair-End insert_len 250 read_len 100 id 1
TGCAATACCATCAAAAATATTTTCCAACATTTGATAAAAAAGGAAAAATTACCAATGAATTTTTAGTTGTGGCAAATAACAATGATGAAAAAGGTTATAT
+
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
@Simulator data , type Pair-End insert_len 250 read_len 100 id 2
ATTGGAACTAATAATAAGATCTATTCATTTGCATCAATTGGAAATGATCCTCAAGATTTAAAATTTGCAGGTGAAGAAACGAAGCTTGAAATTGGTGACA

==> f1_1.fastq <==
@Simulator data , type Pair-End insert_len 250 read_len 100 id 0
TCAACTGGTGTAGTGGTATTAGAACTGCTTCCACCACAGCTCAGATCTGCACTCCAACTATTGTCACTTAGATGCTTTGAAAATGTATTTAATGTGTCTC
+
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
@Simulator data , type Pair-End insert_len 250 read_len 100 id 1
ATTTTGTCAAAATAAGACCCAAGACCTTTAAAATAATTCATATTTTTTAATTTTGAAACTTGTTTAACTAAATTTTGAGATTTATTTTTTTCCCAAAAAA
+
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
@Simulator data , type Pair-End insert_len 250 read_len 100 id 2
CGTTGTTAGCTAGAATAACGTTATCTTCGACTAAACAATCATGTGCTATATGTGAAGAAACCATAAATAAACAGTTATTTCCTACTTTAGTTATTCCACC

```




