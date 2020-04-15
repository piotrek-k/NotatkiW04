#! /bin/bash

# Dany jest katalog D (pierwszy parametr skryptu).
# Należy ponumerować wszystkie pliki regularne w D poprzez dodanie na ich
# końcu członu .N, gdzie N to kolejne liczy naturalne (1, 2, 3 itp.).
# Numeracja powinna przebiegać według wielkości plików (w dowolną stronę).

dir=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -d $dir ]; then
    echo "Argument nie jest katalogiem"
    exit 1
fi

counter=1
for file in `ls -AS ${dir}`; do
    file_path=${dir}/${file}
    
    if [ -f ${file_path} ]; then
        echo "${file_path} ==> ${file_path}.${counter}"
        mv ${file_path} "${file_path}.${counter}"
        
        let "counter=counter+1"
    fi
done