Kompilacja

```
gcc -g zad2.s zad2.c -o executable -m32
```

Dodatkowy argument `-m32` kompiluje dla architektury 32b. Na 64-bitowych systemach trzeba zainstalować 32-bitowe biblioteki.

> apt-get install gcc-multilib

`-g` włącza debugowanie

O `-m32`:

> Similar to the stack- data- and const-align options above, these options arrange for stack frame, writable data and constants to
> all be 32-bit, 16-bit or 8-bit aligned. The default is 32-bit alignment.

Napotkane błędy:

> Error: operand type mismatch for `push'

[W zależności od architektury systemu musimy używać rejestrów o odpowiedniej wielkości wrzucając dane a stos.](https://stackoverflow.com/questions/21245245/c-uses-assemble-operand-type-mismatch-for-push)