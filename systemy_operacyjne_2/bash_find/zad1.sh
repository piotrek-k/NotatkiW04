#! /bin/bash

# Dane są drzewa katalogowe D1 oraz D2 (argument skryptu).
# Należy w D1 oraz D2:
# 1. Usunąć wszystkie pliki .png (nie muszą być to prawdziwe png, liczy się rozszerzenie) o rozmiarze mniejszym niż 200 bajtów (2 p).
# 2. Znaleźć katalogi, do których: właściciel pliku ma prawo odczytu lub inni nie mają prawa wykonania (4 p).
# 3. Znaleźć linki symboliczne do plików innych niż zwykłe (2 p).
# 4. Wypisać dla plików zwykłych: numer i-noda, rozmiar pliku oraz datę ostatniej modyfikacji (3 p).

dir1=$1
dir2=$2

if [ ! -d $dir1 ]; then
    echo "Argument 1. nie jest katalogiem"
    exit 1
fi

if [ ! -d $dir2 ]; then
    echo "Argument 2. nie jest katalogiem"
    exit 1
fi

find -P ${dir1} ${dir2} -maxdepth 3 \
    \( -type f -name "*.png" -exec rm -f {} \; -printf 'Usuwam:\t %p \n' \) -or \
    \( -type d \( -perm -400 -and ! -perm -001 \) -printf 'Katalog z uprawnieniami 1*******0:\t %p \n' \) -or \
    \( -type l -and ! -xtype f -printf 'Link nieprowadzacy do pliku:\t %p \n' \) -or \
    \( -type f -printf '%p:\t inode: %i, size in bytes: %s, modified: %t \n' \)