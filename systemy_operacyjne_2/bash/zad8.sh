#! /bin/bash

dir1=$1
dir2=$2

[ -z "${dir1}" ] && echo "Dir1 not specified" && exit 1
[ -z "${dir2}" ] && echo "Dir2 not specified" && exit 1

dir1_files=`ls "${dir1}"`
for file in ${dir1_files}; do
    if ls ${dir2} | grep --silent ${file}; then
        echo $file
    fi
done