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
