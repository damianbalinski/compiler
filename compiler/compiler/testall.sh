#!/bin/bash

path=$1
dest=$2
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

re='^[0-9]+$'
loops=1

make
make clean

for file in $(find $path -type f); do

    for i in $(seq 1 $loops); do
        echo ""
        echo -e "${GREEN}###################################${NC}"
        echo -e "${GREEN}# ${file}${NC} (${i})"
        echo -e "${GREEN}###################################${NC}"
        ./testsingle.sh $file $dest
    done

    echo "press <num> or \n for more ..."
    read line

    if [[ $line =~ $re ]] ; then
        loops=$((line))
    else
        loops=1
    fi
done

rm ./temp