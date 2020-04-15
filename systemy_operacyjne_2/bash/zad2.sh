#! /bin/bash

# $1 - target directory
# $2 - file containing list of file names to create

for x in `cat $2`; do
    filename="${1}/${x}"
    echo "creating ${filename}"
    touch "${filename}"
done