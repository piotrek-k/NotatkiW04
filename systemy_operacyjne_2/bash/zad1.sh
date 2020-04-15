#! /bin/bash

# $1 - path to directory where all files will have paths '.old' added at the end 

echo $1

for x in `ls $1`; do
    echo "${1}/$x ==> ${1}/${x}.old"
    mv "${1}/$x" "${1}/${x}.old"
done
