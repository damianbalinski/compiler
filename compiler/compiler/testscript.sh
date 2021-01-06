#!/bin/bash

path=$1
RED='\033[0;31m'
PURPLE='\033[1;35m'
NC='\033[0m'

for file in $(find $path -type f); do 
    echo ""
    echo -e "${PURPLE}###################################${NC}"
    echo -e "${PURPLE}# ${file}${NC}"
    echo -e "${PURPLE}###################################${NC}"
    ./myprogram compiler $file ./tests/data
    echo "press \n for more ..."
    read line
done