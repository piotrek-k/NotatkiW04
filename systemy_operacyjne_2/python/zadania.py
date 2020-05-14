# Dane są katalogi K1, K2 oraz T (argumenty skryptu). K1 i K2 są rozumiane jako katalogi „jednopoziomowe”
#   (tzn. interesują nas tylko pliki bezpośrednio w tym katalogu, a nie głębiej), 
#   zaś T jest rozumiane jako całe drzewo katalogowe (dowolnej głębokości). Należy:
# 1. Utworzyć w K2 kopie plików regularnych z K1, do których my (wykonawca skryptu) mamy prawo wykonania. (3)
# 2. W K1 przekształcić wszystkie linki symboliczne do katalogów tak, aby były zdefiniowane ścieżką bezwzględną. (3)
# 3. W T należy znaleźć (wypisać nazwy) katalogi, które zostały utworzone dawniej niż 5 minut temu i które mają co 
#       najwyżej 3 (bezpośrednie) podkatalogi. (4)

import sys
import os, time
from shutil import copyfile

if len(sys.argv) != 4:
    print("Nieodpowiednia ilość argumentów")
    exit(1)

k1  = sys.argv[1]
k2  = sys.argv[2]
t   = sys.argv[3]

with os.scandir(k1) as it:
    for entry in it:
        #source = os.path.join(k1, entry.name)
        source = os.path.abspath(entry.path)

        # ZADANIE 1
        if(os.access(source, os.X_OK)):
            destination = os.path.join(k2, entry.name)
            print("Kopiowanie ", source, "do ", destination)
            copyfile(source, destination)

        # ZADANIE 2
        if entry.is_symlink():
            link_contents = os.readlink(source)
            if not os.path.isabs(link_contents):
                new_link_contents = os.path.join(os.path.dirname(source), link_contents)
                print("Konwersja zawartości linka ", link_contents, " do ", new_link_contents)
                os.remove(source)
                os.symlink(new_link_contents, source)

# ZADANIE 3
for root, dirs, files in os.walk(t):
    # print(root, len(dirs))

    status = os.stat(root)
    mod_time_nanosec = status.st_mtime_ns
    mod_time_minutes = mod_time_nanosec / 6e10
    current_time_min = time.time_ns() / 6e10
    #print(root, "time: ", current_time_min - mod_time_minutes)

    if current_time_min - mod_time_minutes > 5:
        # modyfikacja ponad 5 minut temu
        print(root, " zmodyfikowany ponad 5 minut temu")

    if len(dirs) <= 3:
        print(root, "ma co najwyżej 3 bezpośrednie podkatalogi")

            
                
        