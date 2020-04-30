# Dany jest plik zwykły P (argument skryptu). Należy wypisać ten plik na ekran
# z następującymi zmianami (tylko wypisać, bez zmiany oryginalnego pliku):
# 1. Ponumerować linie pliku (puste też). (1)

file1=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -f $file1 ]; then
    echo "Argument 1. nie jest plikiem"
    exit 1
fi

awk 'BEGIN {line=0} {x+=1; print x": "$0; }' $file1