# Dany jest plik zwykły P (argument skryptu). Należy wypisać ten plik na ekran z następującymi zmianami (tylko wypisać, bez zmiany oryginalnego pliku):
# 1. Ponumerować linie pliku (puste też). (1)
# 2. Nie wypisywać treści komentarzy jednolinijkowych C/C++ (pomijać treść od dwuznaku // do końca linii). (2)
# 3. Zamienić wszystkie daty formatu DD-MM-YYYY (np. 30-04-2020) na YY/MM/DD (20/04/30). Uwaga: daty mogą występować wielokrotnie w tej samej linii! (4)
# 4. Na koniec wypisać nazwy załączonych plików C/C++ (wykrywanie linii typu #include <filename> lub #include "filename"). (3)

file1=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -f $file1 ]; then
    echo "Argument 1. nie jest plikiem"
    exit 1
fi

awk ' \
    BEGIN {line=0} \
    { \
        x+=1; \
        currentResult = x": "$0; \
        commentResult = match( currentResult, /(.*)(\/\/.*)$/, tabComm); if(commentResult) currentResult = tabComm[1]; \
        datesResult = gensub( /([0-9]{2})-([0-9]{2})-[0-9]{2}([0-9]{2})/ , "\\3/\\2/\\1", "g", currentResult ); currentResult = datesResult;
        match( currentResult, /#include\s?[<"]([a-zA-Z0-9\.]+)[">]/, tab ); if(tab[1]) array[arraylen++] = tab[1]; \
        \
        print currentResult; \
    } \
    END { \
        print "\n\nZalaczone pliki:";
        for ( i = 0; i < arraylen; i++ ) \
            print array[i]; \
     } \
    ' $file1