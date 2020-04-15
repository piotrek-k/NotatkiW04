#! /bin/bash

dir=$1
file_name=$2

[ -z "${1}" ] && echo "No dir specified" && exit 1
[ -z "${2}" ] && echo "No filename specified" && exit 1

for file in "$dir"/*; do
    if [ ! -s "$file" ]; then
        # file has 0 size
        echo "${file}" >> "${file_name}"
        rm ${file}
    fi
done