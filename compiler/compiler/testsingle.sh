#!/bin/bash

src=$1
dest=$2
./temp $src $dest

if (( $? == 0 )) ; then
    # compilation ok
    maszyna-wirtualna-cln $dest
    # rm $dest
else
    # compilation error
    echo "Compilation error"
fi
