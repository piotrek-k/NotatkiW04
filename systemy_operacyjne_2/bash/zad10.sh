#! /bin/bash

# Dane są katalogi D1 (pierwszy parametr skryptu) oraz D2 (drugi parametr skryptu). 
# Należy z D1 usunąć wszystkie pliki regularne, które mają swoje odpowiedniki w D2
# (tzn. w D2 też są plikami regularnymi o tej samej nazwie)

dir1=$1
dir2=$2

if [ ! $# -eq 2 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -d $dir1 ]; then
    echo "Argument 1. nie jest katalogiem"
    exit 1
fi

if [ ! -d $dir2 ]; then
    echo "Argument 2. nie jest katalogiem"
    exit 1
fi

for file in `ls -A ${dir1}`; do
    if [ -f ${dir2}/${file} ]; then
        file_to_remove=${dir1}/${file}
        echo "removing ${file_to_remove}"
        rm ${file_to_remove}
    fi
done