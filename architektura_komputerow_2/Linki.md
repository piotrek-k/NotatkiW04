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

[Docs: Dyrektywy asemblera (rezerwacja pamięci)](https://sourceware.org/binutils/docs/as/Pseudo-Ops.html#Pseudo-Ops)

- `.space size [,fill]` - wypełnienie bajtów wartością `fill`
- `.comm symbol , length` - zarezerwuj `length` bitów, do których można się odnieść poprzez wpisanie `symbol` (`.comm liczba1, 4` a potem `mov liczba1(, %rcx, 4), %edi`)

- [Sekcja bss](https://sourceware.org/binutils/docs/as/bss.html#bss) - rezerwacja pamięci dopiero podczas uruchomienia programu (?)

* dane w `data` wliczają się w wagę pliku wykonywalnego (?)

[WIKIBOOKS - instrukcje, składnia](https://en.wikibooks.org/wiki/X86_Assembly)
[Adresowanie: poruszanie się po tablicy, stosie. Oznaczenia sufixów](https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax#Address_operand_syntax)