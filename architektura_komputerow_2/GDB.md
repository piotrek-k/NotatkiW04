## Debugowanie

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

```
# ustal breakpoint pod adresem etykiety "nazwa_etykiety"
(gdb) break *nazwa_etykiety
```

Wyświetlaj po każdym kroku wartość rejestru:

```
display $eax
```

Wyświetlaj zawartość pod

## Wyświetlanie danych

> `x` shows you the contents of a memory address

> `p` shows you the value stored in a named variable

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

Usuń breakpoint

```
d[elete] b[reakpoints] number
```

`number` to numer breakpointa.
Numer można sprawdzić komendą `i[nfo] b[reak]`.

Wyświetl dane znajdujące się pod podanym adresem (status_word: zmienna typu short):

```
x/1tw &status_word
```

Wyświetl liczbę zmiennoprzecinkową z adresu pod value1:

```
# IN ASM
.data
    value2: .float 3.0

# IN GDB
x/fw &value1
```
