.data
format_d: .asciz "%d",  # Łańcuchy znaków wykorzystywane do
format_f: .asciz "%f",  # wywoływania funkcji scanf i printf
nowa_linia: .asciz "\n"
 
.bss
.comm liczba1, 4 # Bufory na liczby typu integer i float
.comm liczba2, 4
 
.text
.global main
 
main:
#
# Pobranie od użytkownika pierwszej liczby - typu całkowitego
#
# Odpowiednik poniższego kodu w C: scanf(&liczba1, "%d");
mov $0, %rax        # Przesyłamy 0 parametrów zmiennoprzecinkowych
mov $format_d, %rdi # Pierwszy parametr całkowity dla scanf
                    # - format w jakim ma zostać zapisany
                    # wynik w buforze
mov $liczba1, %rsi  # Drugi parametr całkowity dla scanf
                    # - adres bufora do które zapisany
                    # ma zostać wynik
call scanf          # Wywołanie funkcji scanf z biblioteki stdio.h
 
 
 
#
# Pobranie od użytkownika drugiej liczby - typu zmiennoprzecinkowego
#
mov $0, %rax        # Przesyłamy 0 parametrów zmiennoprzecinkowych
mov $format_f, %rdi # Pierwszy parametr całkowity dla scanf
                    # - format w jakim ma zostać zapisany
                    # wynik w buforze
mov $liczba2, %rsi  # Drugi parametr całkowity dla scanf
                    # - adres bufora do które zapisany
                    # ma zostać wynik
call scanf          # Wywołanie funkcji scanf z biblioteki stdio.h
 
 
 
#
# Wywołanie funkcji napisanej w C z parametrami
# stało i zmiennoprzecinkowymi
#
mov $1, %rax # Ilość argumentów zmiennoprzecinkowych
             # - przesyłany jest jeden parametr w rejestrze XMM0
             # jeśli było by ich więcej musiały by one zostać
             # umieszczone w kolejnych rejestrach XMM
mov $0, %rdi # Czyszczenie rejestru RDI - do jego młodszych
             # czterech bajtów wpisana zostanie wartość
             # wczytanej liczby typu int
mov $0, %rcx # Licznik na potrzeby adresacji pamięci niżej
mov liczba1(, %rcx, 4), %edi # Przeniesienie pierwszego parametru
                             # - typu całkowitego do rejestru RDI
movss liczba2, %xmm0  # Przeniesienie drugiego parametru
                      # - typu zmiennoprzecinkowego do rejestru XMM0
call funkcja          # Wywołanie funkcji
cvtps2pd %xmm0, %xmm0 # Konwersja wyniku na double aby możliwe było
                      # wyświetlenie go przez funkcje printf
 
 
 
#
# Wyświetlenie wyniku z użyciem funkcji printf
#
mov $1, %rax # Przesyłamy jeden parametr zmiennoprzecinkowy
             # - liczbę do wyświetlenia (w rejestrze XMM0)
mov $format_f, %rdi # Pierwszy parametr typu całkowitego
                    # - format w jakim wyświetlona ma zostać liczba
sub $8, %rsp # Workaround, aby printf nie zmienił wartości
             # ostatniej komórki na stosie. Jest to potrzebne tylko
             # przy wyświetlaniu liczb zmiennoprzecinkowych.
             # Wskaźnik na stos należy przesunąć o wielokrotność
             # liczby 8 równą ilości parametrów ZP (8*RAX).
call printf  # Wywołanie funkcji printf
add $8, %rsp # Workaround -||-
 
 
 
#
# Wyświetlenie znaku nowej linii
#
mov $0, %rax # Nie przesyłamy żadnych parametrów ZP
mov $nowa_linia, %rdi # Pierwszy parametr typu całkowitego
                      # - wskaźnik na ciąg znaków do wyświetlenia
                      # - znak nowej linii
call printf # Wywołanie funkcji printf
 
 
 
#
# Zwrot wartości EXIT_SUCCESS
#
mov $0, %rax # Brak parametrów zmiennoprzecinkowych
call exit