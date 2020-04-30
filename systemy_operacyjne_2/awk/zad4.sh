# Dany jest plik zwykły P (argument skryptu). Należy wypisać ten plik na ekran
# z następującymi zmianami (tylko wypisać, bez zmiany oryginalnego pliku):
# 4. Na koniec wypisać nazwy załączonych plików C/C++
# (wykrywanie linii typu #include <filename> lub #include "filename"). (3)

file1=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -f $file1 ]; then
    echo "Argument 1. nie jest plikiem"
    exit 1
fi

awk '{ \
        match( $0, /#include\s?[<"]([a-zA-Z0-9\.]+)[">]/, tab ); if(tab[1]) array[arraylen++] = tab[1]; \
     } \
     END { \
        print "INCLUDED FILES:";
        for ( i = 0; i < arraylen; i++ ) \
            print array[i]; \
     } \
    ' $file1