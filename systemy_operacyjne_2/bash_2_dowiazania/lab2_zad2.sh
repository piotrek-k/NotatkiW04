#! /bin/bash

# Dany jest katalog D (argument skryptu). Należy w nim zmienić
# wszystkie dowiązania symboliczne tak by były zdefiniowane ścieżką
# względną (i wskazywały na to same miejsce co przed zamianą).
# Stworzenie ścieżki względnej inaczej niż „ręcznie” jest nisko punktowane.

dir1=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -d $dir1 ]; then
    echo "Argument 1. nie jest katalogiem"
    exit 1
fi

for file in `ls -AS ${dir1}`; do
    user_provided_path="${dir1}/${file}"                # sciezka podana przez uzytkownika
    echo "${user_provided_path}"

    file_can_path=`realpath -s ${user_provided_path}`   # sciezka do dowiazania
    ln_can_path=`readlink -f ${file_can_path}`          # sciezka do zalinkowanego przez dowiazanie pliku

    echo "file_can_path ${file_can_path}"
    echo "ln_can_path ${ln_can_path}"

    # znalezienie wspólnego basename
    common_basename = ""                                # część wspólna obu ścieżek
    steps_back=""                                       # "kroki w tył" z perspektywy lokalizacji dowiązania
    
    # Przeszukuje wszystkie możliwe kombinacje ścieżek
    current_dirname=`dirname ${file_can_path}`
    found=false
    while [ $current_dirname != "." ] && [ $current_dirname != "/" ] && [ $found = false ]
    do
        echo "current_dirname ${current_dirname}"
        ln_dirname=`dirname ${ln_can_path}`
        while [ $ln_dirname != "." ] && [ $ln_dirname != "/" ] && [ $found = false ]
        do
            echo "ln_dirname ${ln_dirname}"
            if [ ${current_dirname} = ${ln_dirname} ]; then
                found=true
                common_basename=${current_dirname}
                echo "Znaleziono wspolna sciezke ${current_dirname}"
            fi
            ln_dirname=`dirname ${ln_dirname}`
        done
        if [ $found = false ]; then
            steps_back="../${steps_back}"
        fi
        current_dirname=`dirname ${current_dirname}`
    done

    result="${ln_can_path/$common_basename/$steps_back}"
    echo "${result}"

    ln -sf $result $file_can_path

done