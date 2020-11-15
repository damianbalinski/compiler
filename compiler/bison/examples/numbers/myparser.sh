#!/bin/bash

flex -o flex.c $1.l 
bison -d -o bison.c $1.y
gcc flex.c bison.c -o temp -O3 -lfl
./temp