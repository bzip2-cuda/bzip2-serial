#!/bin/sh

#g++ -o bin/cbz2 src/main.cpp src/file.cpp src/bzip2.cpp
g++ -o bin/cbz2 src/main.cpp src/bzip2.cpp -lboost_regex #src/file.h src/rle.h
#g++ -o bin/cbz2 src/main.cpp
