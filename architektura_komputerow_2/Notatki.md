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
