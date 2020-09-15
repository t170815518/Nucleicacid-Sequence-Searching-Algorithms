cmake_minimum_required(VERSION 3.17)
project(PatternSearchProgram)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PatternSearchProgram
        BruteForce.c
        BruteForce.h
        FNAFilePreprocess.c
        FNAFilePreprocess.h
        KMPAlgorithm.c
        KMPAlgorithm.h
        main.c
        RabinKarpAlgorithm.c
        RabinKarpAlgorithm.h)
