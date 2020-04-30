# Dany jest plik zwykły P (argument skryptu). Należy wypisać ten plik na ekran
# z następującymi zmianami (tylko wypisać, bez zmiany oryginalnego pliku):
# 2. Nie wypisywać treści komentarzy jednolinijkowych C/C++ (pomijać treść od dwuznaku // do końca linii). (2)

file1=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -f $file1 ]; then
    echo "Argument 1. nie jest plikiem"
    exit 1
fi

# awk 'BEGIN { FS="//"; } { print $1; }' $file1
awk '{ result = match( $0, /(.*)(\/\/.*)$/, tabComm); if(result) print tabComm[1]; else print $0; }' $file1