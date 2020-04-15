#! /bin/bash

for file in $1/*; do
    if [ ! -x $file ]; then
        echo "Removing $file"
        rm -rf $file
    fi
done