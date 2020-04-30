# Dany jest plik zwykły P (argument skryptu). Należy wypisać ten plik na ekran
# z następującymi zmianami (tylko wypisać, bez zmiany oryginalnego pliku):
# 3. Zamienić wszystkie daty formatu DD-MM-YYYY (np. 30-04-2020) na YY/MM/DD (20/04/30).
# Uwaga: daty mogą występować wielokrotnie w tej samej linii! (4)

file1=$1

if [ ! $# -eq 1 ]; then
    echo "Nieprawidlowa ilosc argumentow"
    exit 1
fi

if [ ! -f $file1 ]; then
    echo "Argument 1. nie jest plikiem"
    exit 1
fi

awk '{ result = gensub( /([0-9]{2})-([0-9]{2})-[0-9]{2}([0-9]{2})/ , "\\3/\\2/\\1", "g", $0 ); print result; }' $file1