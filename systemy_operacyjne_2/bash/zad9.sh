#! /bin/bash

set -o nounset

dir=$1

[ -z ${dir} ] && echo "Dir not specified" && exit 1

for dir_inside in ${dir}/*; do
    if [ -d ${dir_inside} ]; then
        mv ${dir_inside}/* ${dir}
    fi
done