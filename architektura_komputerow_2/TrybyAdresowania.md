# Tryby adresowania

```
ADDRESS_OR_OFFSET(%BASE_OR_OFFSET,%INDEX,MULTIPLIER)
```

Co daje w wyniku:

```
FINAL ADDRESS = ADDRESS_OR_OFFSET + %BASE_OR_OFFSET + MULTIPLIER * %INDEX
```

`ADDRESS_OR_OFFSET` i `MULTIPLIER` muszą być wartościami stałymi. Pozostałe wartości muszą być rejestrami. Pominięte wartości zamienione są na 0.

### Direct addressing mode

```
movl ADDRESS, %eax
```

Zapisz do %eax **wartość** z adresu ADDRESS

### Indexed addressing mode

```
movl string_start(,%ecx,1), %eax
```

Ładuje wartość z start_string+1\*%eax do %eax

### Indirect addressing mode

%eax zawiera adres do danych. Przenieś te dane do %ebx

```
movl (%eax), %ebx
```

### Immediate mode

Zapisanie liczby 12 do eax

```
movl $12, %eax
```
Przeniesienie adresu `char` do ebx
```
mov $char, %ebx
```
Gdzie `char` to 
```
.bss
	.comm char, 1
```
