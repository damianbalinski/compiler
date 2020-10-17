#!/bin/bash

cat "test.txt"
echo ""
echo "----------------------"
flex -o test.c "$1"
gcc test.c -O3 -lfl -o test
./test < "test.txt"
rm test.c test