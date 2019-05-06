
# Procedure calls

[źródło](http://www.zak.ict.pwr.wroc.pl/materials/architektura/laboratorium%20AK2/Dokumentacja/Intel%20Penium%20IV/IA-32%20Intel%20Architecture%20Software%20Developers%20Manual%20vol.%201%20-%20Basic%20Architecture.pdf)

## Stos
Blok danych zawarty w segmencie (?) identifikowany przez rejestr `SS`. Stos może mieć wielkość max. 4GB (masksymalna wielkość segmentu).

Wrzucając wartść na stos, *zmniejszamy* rejestr ESP. Stos "rośnie w dół". 

Inicjalizacja stosu:
1.    Establish a stack segment.
2.    Load the segment selector for the stack segment into the SS register using a MOV, POP, orLSS instruction.
3.    Load  the  stack  pointer  for  the  stack  into  the  ESP  register  using  a  MOV,  POP,  or  LSSinstruction.  (The  LSS  instruction  can  be  used  to  load  the  SS  and  ESP  registers  in  oneoperation.)

## Near CALL
Komenda CALL przenosi wywoływanie programu w ramach aktualnego segmentu. Umożliwia dostęp do procedur wewnątrz obecnie działającego progamu lub zadania (task).
* Przenosi zawartość EIP na stos
*  Loads the offset of the called procedure in the EIP register (?)
* Rozpoczyna wywoływanie procedury

## Near RET
* Przenosi (pop) szczyt stosu do EIP
* Jeśli instrukcja RET ma opcjonalny argument `n`, zwiększa wskaźnik stosu o ilość `n` (?) bajtów. (stos zwiększa się od największej do najemiejszej wartości, czyli usuwamy dane ze stosu)
* Wznawia wykonywanie procedury (która wywołała CALL?)

## Far CALL
Wywoływanie funkcji z innych segmentów kodu (takich jak procedury systemu operacyjnego).
* Rejestr CS wchodzi na stos, potem EIP
* Loads  the  segment  selector  of  the  segment  that  contains  the  called  procedure  in  the  CS register (?)
* offset wywoływanej procedury zapisany do EIP
* wywołuje żądaną procedurę

## Far RET
* top-of-stack -> EIP
* top-of-stack -> CS
* zwiększa wskaźnik stosu o `n` (jeśli podane)
* Wznawia wykonywanie procedury 

## Przekazywanie parametrów
* Poprzez rejestry (przez co można przesłać do 6 paramterów) (ESP i EBP nie mogą być do tego użyte). Wywołana procedura może też w ten sposób przekazać wyniki.
* Dużą liczbę parametrów można przekazać poprzez stos. Here, it is useful to use the stack-framebase pointer (in the EBP register) to make a frame boundary for easy access to the parameters.
* Przekazanie adresu w pamięci

## Zapisywanie stanu procedury przed wywoływaniem CALL
`PUSHA` zapisuje `general-purpose registers` na stos w kolejności `EAX, ECX, EDX, EBX, ESP, EBP, ESI, and EDI`.

`POPA` przywraca zapisane wartości.

`PUSHF(lower word)/PUSHFD(entire register), POPF/POPFD` mogą być użyte dla rejestru `EFLAGS`.