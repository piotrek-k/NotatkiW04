# Linki

[Guide to GDB](http://apoorvaj.io/hitchhikers-guide-to-the-gdb.html#gdbinit)

[GDB Cheatsheet](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)

[AT&T assembly syntax and IA-32 instructions](https://gist.github.com/mishurov/6bcf04df329973c15044)

[Asembler x86/Architektura (opis rejestrów)](https://pl.wikibooks.org/wiki/Asembler_x86/Architektura)

[sesja.txt (podstawowe komendy w terminalu)](http://zak.ict.pwr.wroc.pl/materials/architektura/laboratorium%20AK2/sesja.txt)

[Podstawowe komendy programu](https://zeszyt.olo.ovh/2016/02/28/architektura-komputerow-2-laboratorium-nr-1-podstawy-pisania-programow-w-jezyku-asembler/)

[Dokumentacja Intela - Instruction Set Reference](http://www.zak.ict.pwr.wroc.pl/materials/architektura/laboratorium%20AK2/Dokumentacja/Intel%20Penium%20IV/IA-32%20Intel%20Architecture%20Software%20Developers%20Manual%20vol.%202%20-%20Instruction%20Set%20Reference.pdf)

[Docs: Memory references](https://sourceware.org/binutils/docs/as/i386_002dMemory.html#i386_002dMemory)

[Docs: Instruction naming](https://sourceware.org/binutils/docs/as/i386_002dMnemonics.html#Instruction-Naming)

[WIKIBOOKS - instrukcje, składnia](https://en.wikibooks.org/wiki/X86_Assembly)
[Adresowanie: poruszanie się po tablicy, stosie. Oznaczenia sufixów](https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax#Address_operand_syntax)

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
