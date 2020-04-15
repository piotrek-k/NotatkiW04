#! /bin/bash
# move executable regular files from d1 to d2

source_path=$1
dest_path=$2

for file in "$source_path"/*; do
    if [ -x "$file" ] && [ -d "$dest_path" ]; then
        echo "moving ${file}"
        mv "$file" "${dest_path}/"
    fi
done