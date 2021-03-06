## Wyświetlenie binarnej zawartości pliku:

(sprawdzić)

```
xxd -b nazwa_pliku
```

## Zwartość pliku (szesnastkowo+adresy+reprezentacja ascii)

```
$ hexdump -C rw
00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
00000010  02 00 3e 00 01 00 00 00  86 00 40 00 00 00 00 00  |..>.......@.....|
00000020  40 00 00 00 00 00 00 00  d0 00 00 00 00 00 00 00  |@...............|
00000030  00 00 00 00 40 00 38 00  01 00 40 00 05 00 02 00  |....@.8...@.....|
00000040  01 00 00 00 05 00 00 00  00 00 00 00 00 00 00 00  |................|
00000050  00 00 40 00 00 00 00 00  00 00 40 00 00 00 00 00  |..@.......@.....|
00000060  a8 00 00 00 00 00 00 00  a8 00 00 00 00 00 00 00  |................|
00000070  00 00 20 00 00 00 00 00  48 65 6c 6c 6f 2c 20 77  |.. .....Hello, w|
00000080  6f 72 6c 64 21 0a b8 04  00 00 00 bb 01 00 00 00  |orld!...........|
00000090  b9 78 00 40 00 ba 0e 00  00 00 cd 80 b8 01 00 00  |.x.@............|
000000a0  00 bb 00 00 00 00 cd 80  00 2e 73 79 6d 74 61 62  |..........symtab|
000000b0  00 2e 73 74 72 74 61 62  00 2e 73 68 73 74 72 74  |..strtab..shstrt|
000000c0  61 62 00 2e 74 65 78 74  00 00 00 00 00 00 00 00  |ab..text........|
000000d0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
[...]
000002d0  37 00 00 00 00 00 f1 ff  0e 00 00 00 00 00 00 00  |7...............|
000002e0  00 00 00 00 00 00 00 00  3e 00 00 00 10 00 01 00  |........>.......|
000002f0  86 00 40 00 00 00 00 00  00 00 00 00 00 00 00 00  |..@.............|
00000300  45 00 00 00 10 00 f1 ff  00 10 60 00 00 00 00 00  |E.........`.....|
00000310  00 00 00 00 00 00 00 00  51 00 00 00 10 00 f1 ff  |........Q.......|
00000320  00 10 60 00 00 00 00 00  00 00 00 00 00 00 00 00  |..`.............|
00000330  58 00 00 00 10 00 f1 ff  00 10 60 00 00 00 00 00  |X.........`.....|
00000340  00 00 00 00 00 00 00 00  00 45 58 49 54 5f 4e 52  |.........EXIT_NR|
00000350  00 52 45 41 44 5f 4e 52  00 57 52 49 54 45 5f 4e  |.READ_NR.WRITE_N|
00000360  52 00 53 54 44 4f 55 54  00 45 58 49 54 5f 43 4f  |R.STDOUT.EXIT_CO|
00000370  44 45 5f 53 55 43 43 45  53 53 00 6d 73 67 00 6d  |DE_SUCCESS.msg.m|
00000380  73 67 4c 65 6e 00 5f 73  74 61 72 74 00 5f 5f 62  |sgLen._start.__b|
00000390  73 73 5f 73 74 61 72 74  00 5f 65 64 61 74 61 00  |ss_start._edata.|
000003a0  5f 65 6e 64 00                                    |_end.|
000003a5
```

## Z kodu C wygeneruj kod ASM:

```
$ gcc -S HelloWorld.c -o HelloWorld.s
```

## Dissasemble executable file:

```
$ objdump -d zadanie

zadanie:     file format elf32-i386


Disassembly of section .init:

080482e0 <_init>:
 80482e0:	55                   	push   %ebp
 80482e1:	89 e5                	mov    %esp,%ebp
 80482e3:	53                   	push   %ebx
 80482e4:	83 ec 04             	sub    $0x4,%esp
 80482e7:	e8 00 00 00 00       	call   80482ec <_init+0xc>
 80482ec:	5b                   	pop    %ebx
 80482ed:	81 c3 08 1d 00 00    	add    $0x1d08,%ebx

```

## Zestawienie kodu asemblerowego z jego binarną reprezentacją w pliku

```
as -alh zadanie.s --32
```

```
GAS LISTING zadanie.s 			page 1


   1              	SYSCALL32 = 0x80 # wywołanie funkcji standardowej
   2              	EXIT = 1 # nr funkcji restartu (=1) – zwrot sterowania do s.o.
   3              	EXIT_SUCCESS = 0
   4              	.bss
   5              		.comm short, 2
   6              		.comm char, 1
   7
   8              	.data
   9 0000 506F6461 		msg_short: .asciz "Podaj wartosc short:"			 # ciąg znaków kończący się znakiem \0
   9      6A207761
   9      72746F73
   9      63207368
   9      6F72743A
  10 0015 506F6461 		msg_char: .asciz "Podaj wartosc char:"
[...]
```
