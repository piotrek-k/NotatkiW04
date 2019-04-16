# SVN

Dostęp do repozytorium

```
svn checkout [adress]
```

```
svn add [sciezka]
```

```
svn commit -m [msg]
```

```
svn update
```

```
svn log -v
```

# Kompilacja

Generowanie pliku obiektowego. `-gstabs` pozwala na tworzenie breakpointów w gdb

```
as -o ./build/zadanie.o zadanie.s -gstabs
```

Generowanie pliku wykonywalnego

```
ld -o ./build/zadanie ./build/zadanie.o
```

Debugowanie

```
gdb [sciezka]
```

Input z pliku:

```
(gdb) run < [sciezka do pliku wejsciowego]
```

Podgląd adresów:

```
disas/disasseble
```

Breakpoint na adresie:

```
break *[adres]
```

Wyświetlaj po każdym kroku wartość rejestru:

```
display $eax
```

# Narzędzia

Wyświetlenie kodu ASCII z pliku binarnego (Canonical hex+ASCII display):

```
hexdump -c [sciezka]
```

# GDB

## Debugowanie

```
# ustal breakpoint pod adresem etykiety "nazwa_etykiety"
(gdb) break *nazwa_etykiety
```

## Wyświetlanie danych

[Manual GDB - wskazówki dotyczące wyświetlania danych](ftp://ftp.gnu.org/old-gnu/Manuals/gdb/html_chapter/gdb_9.html#SEC56)

Wyświetlenie 8 jednostek w formacie binarnym o wielkości jednego bajta

```
(gdb) display/format expr
(gdb) display/format addr
```

`format` - > `nfu`

Ilość powtórzeń (`n`): domyślnie 1

Formaty wyświelania (`f`):

- `x` - traktuj bity jako int, wyświetl w hex
- `d` - wyświetl w systemie dziesiętnym ze znakiem
- `u` - sys. dzies. bez znaku
- `o` - int jako octal
- `t` - int jako wartość binarna
- `c` - int jako char
- `f` - bity jako liczba zmiennoprzecinkowa

Wielkość wyświetlanej jednostki (`u`):

- `b` - bajt
- `h` - halfword (dwa bajty)
- `w` - słowo (4 bajty)
- `g` - giant word (8 bajtów)

```
# wyświetl jedno ośmiobajtowe słowo w formacie binarnym
(gdb) display/1tg &buf
```
