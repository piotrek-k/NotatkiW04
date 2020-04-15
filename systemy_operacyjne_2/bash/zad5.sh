#! /bin/bash
# display files for which we have write permission

folder_path=$1

for file in $folder_path/*; do
    if [ -r $file ]; then
        echo "====" $file "===="
        cat $file 
        echo ""
    else
        echo "==== ${file} not readable"
    fi;
done