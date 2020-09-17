#  Pattern Searching For Nucleic Acid Sequence

*This project is for CZ2001 Lab Project* 

## Set-up Instructions 

1. Download the files
2. `cmake` is recommended for building the files. Ensure `cmake` has been installed on the machine properly.
3. Type `cmake PATH_OF_PROJECT`
4. Go to the project directory and type `make`. An exetuable will be generated.
5. Type `./PatternSearchProgram` to start.

## Dataset

All fna files shoule be placed within `dataset` direcoty. 

## Limits

All the limits below are stored in `FNAFilePreprocess.c` as constants.

By default, 

+ `MAX_OCCURRENCES = 100;` only 100 occurrences will be saved and printed.
+ `MAX_LENGTH = 10000000000;` the maximum size of char array to search.
+ `MAX_INPUT = 100000;` the maximum size of char array as pattern. 

## Command Instructions 

The syntax of the command: 

```bash
./lab algorithm dataset 
```

`dataset` refers to the file name of the dataset in `dataset` directory. 

### Algorithm provided 

+ Brute-force (baseline): `b`
+ KMP `kmp`
+ Rabin-Karp Algorithm (with ntHash):  `rk` for native approach, `rk-nt` for improved approach.

### Example

```bash
./lab b # brute force 
./lab kmp # kmp
./lab rk # rabin-karp
./lab rk-nt # rabin-karp improved 
```

#### Example output

```bash
$ ./lab b dna.200MB
Type the target pattern to search (type -1 to exit the program): ATTTTTAAA
==========There are more than 100 occurrences. Only 100 of them are displayed.==========
==========100 occurrences found in total==========
228 28938 49972 98372 111015 115709 117858 187711 194151 198795 230510 248492 269475 334826 354494 364840 368696 440620 449627 450115 489754 491538 498969 513195 536035 563867 583656 588688 589334 603625 625168 658083 664082 705927 706224 708156 760241 774028 840812 850791 875310 915237 938824 939912 952617 958815 959921 965519 974771 987513 992045 996135 1006473 1019071 1023406 1046237 1112414 1112951 1122937 1131746 1134522 1158251 1178889 1185209 1192826 1211380 1253254 1255343 1267294 1285937 1307427 1333256 1341678 1351630 1362173 1370110 1383214 1404948 1410534 1420319 1421537 1427632 1482318 1492182 1506058 1513963 1518029 1521059 1539806 1541680 1547959 1550251 1558951 1559607 1569862 1619107 1630623 1716645 1731871 1735370 
==========Execution time = 27.019000==========
Type the target pattern to search (type -1 to exit the program): -1

$ ./lab rk-nt dna.200MB
==========Random Numbers Generated==========
G = 2089631732
A = 847563288
C = 2635165145
T = 4110930313
U = 4088102620
Type the target pattern to search (type -1 to exit the program): ATTTTTAAA
==========There are more than 100 occurrences. Only 100 of them are displayed.==========
==========0/100 times of collisions==========
==========100 occurrences found in total==========
228 28938 49972 98372 111015 115709 117858 187711 194151 198795 230510 248492 269475 334826 354494 364840 368696 440620 449627 450115 489754 491538 498969 513195 536035 563867 583656 588688 589334 603625 625168 658083 664082 705927 706224 708156 760241 774028 840812 850791 875310 915237 938824 939912 952617 958815 959921 965519 974771 987513 992045 996135 1006473 1019071 1023406 1046237 1112414 1112951 1122937 1131746 1134522 1158251 1178889 1185209 1192826 1211380 1253254 1255343 1267294 1285937 1307427 1333256 1341678 1351630 1362173 1370110 1383214 1404948 1410534 1420319 1421537 1427632 1482318 1492182 1506058 1513963 1518029 1521059 1539806 1541680 1547959 1550251 1558951 1559607 1569862 1619107 1630623 1716645 1731871 1735370 
==========Execution time = 19.406000==========
Type the target pattern to search (type -1 to exit the program): -1

```



