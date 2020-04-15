#! /bin/bash

# Dany jest katalog D oraz plik zwykły P (dwa argumenty skryptu).
# Należy w D usunąć wszystkie dowiązania symboliczne wiszące (zepsute)
# a następnie zamienić wszystkie dowiązania symboliczne w D do pliku P na dowiązania twarde.

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

for file in `ls -AS ${dir1}`; do
    
    full_file_path="${dir1}/${file}"
    
    if [ -L ${full_file_path} ]; then
        # jest dowiązaniem symbolicznym
        if [ ! -e ${full_file_path} ]; then
            # plik wskazywany przez link nie istnieje
            # usunięcie dowiązania
            echo "Usuniecie ${full_file_path}"
            rm ${full_file_path}
        fi
    fi
done

for file in `ls -AS ${dir1}`; do
    
    full_file_path="${dir1}/${file}"

    if [ -L ${full_file_path} ]; then
        # jest dowiązaniem symbolicznym
        abs_path=`readlink -f ${full_file_path}`
        echo "${full_file_path} wskazuje na ${abs_path}"
        
        if [ "${file1}" -ef "${abs_path}" ]; then
            # dowiązanie wskazuje na plik P

            # zamiana na link twardy
            echo "Zamiana na link twardy"
            ln -f ${abs_path} "${full_file_path}" 
        fi
    fi
done