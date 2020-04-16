#! /bin/bash

# – dla każdego dowiązania symbolicznego należy wypisać jego (lub ewentualnie celu) nazwę (ostatni człon) zaszyfrowaną dowolnym szyfrem cezara, (3)
# – dla każdego katalogu wypisać liczbę jego (bezpośrednich) ukrytych plików, (3)
# – dla każdego pliku, którego nazwa zaczyna się na literę n lub N wypisać jego ścieżkę bezwzględną z zamianą ukośników na odwrotne. (3)
# Wyniki należy posortować, wysłać do pliku P, odwrócić kolejność linii oraz wyświetlić na ekranie ostatnie 7 wyników. (3)

dir1=$1
file1=$2

if [ ! $# -eq 2 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -d $dir1 ]; then
    echo "Argument 1. nie jest katalogiem"
    exit 1
fi

if [ ! -f $file1 ]; then
    echo "Argument 2. nie jest plikiem regularnym"
    exit 1
fi

find ${dir1} \
    \( -type l -printf 'link %f\n' \) -or \
    \( -type d -printf 'hidden ' -exec sh -c 'find $1 -maxdepth 1 -type f -name ".*" | grep -c /' sh {} \; \) -or \
    \( -type f -iname "n*" -printf 'nfile ' -exec readlink -f {} \; \) \
| while read comm_type argument
    do
        # echo "=== READING ${comm_type} ${argument}"
        if [ "${comm_type}" = 'link' ]; then
            # szyfr cezara
            result=`echo ${argument} | tr '[A-Za-z]' '[N-ZA-Mn-za-m]'`
            printf "${result}\n"
        fi

        if [ "${comm_type}" = 'hidden' ]; then
            # bezposrednie ukryte pliki
            printf "${argument}\n"
        fi

        if [ "${comm_type}" = 'nfile' ]; then
            # zamiana ukosnikow na odwrotne
            printf "${argument//\//\\\\}\n"
        fi
    done \
| sort | tee ${file1} | rev | tail --lines=7
