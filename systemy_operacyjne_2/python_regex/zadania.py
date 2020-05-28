"""
Dane jest drzewo katalogowe D i dwa pliki zwykłe P1 i P2 (argumenty skryptu).
1. W D dla każdego linku symbolicznego należy wyświetlić jego nazwę (ostatni człon) oraz liczbę znaków jaka jest w nim (linku) zapisana, zaś dla każdego pliku zwykłego należy wyświetlić jego nazwę (ostatni człon) oraz liczbę linii tego pliku zawierających napis "hello". (3 pt)
2. Wyniki z punktu 1 należy dodatkowo zapisać do P1 po czym posortować (przed wyświetleniem) wg nazwy pliku. (2 pt)
3. Należy wypisać na ekran zawartość pliku P2 z wszystkimi datami postaci YYYY-MM-DD zamienionymi na postać MM.DD.YY. Daty są zawsze oddzielone co najmniej jednym znakiem (ale niekoniecznie spacją). Może być więcej niż jedna data w jednej linii. (4 pt)
"""

import sys
import os
import re

if len(sys.argv) != 4:
    print("Nieodpowiednia ilość argumentów")
    exit(1)

d_relpath = sys.argv[1]
p1_relpath = sys.argv[2]
p2_relpath = sys.argv[3]

if not os.path.isdir(d_relpath) or not os.path.isfile(p1_relpath) or not os.path.isfile(p2_relpath):
    print("Nieodpowiednie argumenty")
    exit(1)

results = {}

print("===== ZADANIE 1 ======")

with os.scandir(d_relpath) as it:
    for entry in it:

        # ZADANIE 1

        file_name = entry.name

        if entry.is_symlink():
            text = os.readlink(entry.path)

            print("Link: nazwa: ", file_name, "\t ilość znaków: ", len(text))

            results[file_name] = len(text)

        elif entry.is_file():
            with open(entry.path, "r") as fobj:
                text = fobj.read()
                reg = re.compile(r"^.*(hello)+.*$", re.M)
                result = re.findall(reg, text)
                # print("Ilosc linii z hello: ", len(result))

                results[file_name] = len(result)

                print("Plik: nazwa: ", file_name, "\t ilość linii z 'hello'", len(result))

# ZADANIE 2

print("===== ZADANIE 2 ======")

# Zapisanie do pliku
p1 = open(p1_relpath, "w")
for key, value in results.items():
    p1.write(key + "\t" + str(value) + "\n")

# Posortowanie, wyświetlenie
for key in sorted(results):
    print(key, "\t", results[key])

# ZADANIE 3

print("===== ZADANIE 3 ======")

def date_changer(m):
    year = m.group(1)
    month = m.group(2)
    day = m.group(3)
    year = year[:2]

    result = month + "." + day + "." + year
    #print(result)
    return result

with open(p2_relpath, "r") as fobj:
    text = fobj.read()
    reg = re.compile(r"(?<!\d)(\d{4})\-(\d{2})\-(\d{2})(?!\d)", re.M)
    changed_text = re.sub(reg, date_changer, text)

    print(changed_text)