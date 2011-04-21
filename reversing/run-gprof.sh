#!/bin/sh

#if [ $# -eq 0 ]
#then
#    i="bananas"
#else
    i=$1
#fi

#echo "Input = $i"

a=`cat ./tst/$i`

echo "Burrows-Wheeler Transform: "
time ./bin/bwt-gprof.out "$a"
gprof ./bin/bwt-gprof.out > gprof/bwt.$i
echo "
Move-To-Front Transform: "
time ./bin/mtf-gprof.out "$a"
gprof ./bin/mtf-gprof.out > gprof/mtf.$i
#echo "
#Huffman encoding / decoding: "
#time ./bin/huffman-gprof.out "$a"
#gprof ./bin/huffman-gprof.out > gprof/huffman.$1
