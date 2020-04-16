#! /bin/bash

# Należy wyświetlić liczbę plików zwykłych na poszczególnych poziomach drzewa.

dir1=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -d $dir1 ]; then
    echo "Argument 1. nie jest katalogiem"
    exit 1
fi

find ${dir1} -type d | while read path
    do
        printf "${path} ("
        find ${path} -maxdepth 1 -type f | grep -c / | tr "\n" "\0"
        printf ")\n"
    done