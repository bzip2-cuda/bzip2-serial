#!/bin/sh

if [ $# -eq 0 ]
then
    i="bananas"
else
    i=$1
fi

echo "Input = $i"

echo "Burrows-Wheeler Transform: "
./bin/bwt.out $i
echo "
Move-To-Front Transform: "
./bin/mtf.out $i
echo "
Huffman encoding / decoding: "
./bin/huffman.out $i
