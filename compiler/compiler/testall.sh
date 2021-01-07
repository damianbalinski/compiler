#!/bin/bash

path=$1
dest=$2
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

make
make clean

for file in $(find $path -type f); do 
    echo ""
    echo -e "${GREEN}###################################${NC}"
    echo -e "${GREEN}# ${file}${NC}"
    echo -e "${GREEN}###################################${NC}"
    ./testsingle.sh $file $dest
    echo "press \n for more ..."
    read line
done

rm ./temp