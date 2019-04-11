# Typy okablowania
[Źrodło](http://itfocus.pl/dzial-it/sieci/okablowanie-kabel-normalny-czy-krosowany/)
* kabel normalny (traight-trought cable) (przewody na obu końcówkach w tej samej kolejności, w standardzie 568A lub 568B)
    - switch do routera
    - switch do komputera/serwera
    - hub do komputera serwera
* kabel krosowany (cross-over cable) (jeden koniec w 568A, drugi w 568B),
    - przełącznik (switch) do przełącznika,
    - przełącznik (switch) do koncentratora (hub),
    - koncentrator (hub) do koncentratora,
    - router do routera,
    - komputer do routera,
    - komputer do komputera
* kabel konsolowy (console cable) (rollover?) (podłączenie komputera do gniazada kosnolowego routera) (kolor niebieski).

# Cisco IOS

## Tryby
Wejście w tryb uprzywilejowany (EXEC)
```
Switch> enable
Switch# <--- znak zachęty w trybie EXEC
```

Tryb konfiguracji globalnej:
```
Switch# configure terminal
Switch(config)# <--- znak zachęty w konfiguracji globalnej
```


## Informacje

Wersja IOS
```
show version
```

Wyświetlenie konfiguracji zegara
```
show clock
```
Znak zapytania podpowiada składnię
```
Switch# clock set ?
    hh:mm:ss  Current Time
```

Wyświetl konfigurację (routera ładowaną po restarcie?)
```
S1# show running-config
```
lub `show run` (?)

Status podłączonych interfejsów przełącznika:
```
S1# show ip interface brief
Interface              IP-Address      OK? Method Status Protocol
Vlan1          unassigned      YES unset  up              up
FastEthernet0/1        unassigned      YES unset  up      up
FastEthernet0/2        unassigned      YES unset  down    down
FastEthernet0/3        unassigned      YES unset  down    down
FastEthernet0/4        unassigned      YES unset  down    down
[...] 
```

Podejrzenie pamięci flash
```
Switch# show flash
```

## Ustawienia

Ustawienie zegara:
```
Switch# clock set 15:08:00 Oct 26 2012
```
Zmiana nazwy przełącznika
```
Switch(config)# hostname Nowa_nazwa_przelacznika
```
Zapobieganie niepożądanym zapytaniom DNS (zapobiegnięcie próbom tłumaczenia niepoprawnie  wprowadzonych poleceń na nazwy hostów)
```
S1(config)# noipdomain-lookup
```
Konfiguracja bannera motd (ze znakiem ograniczającym #)
```
S1(config)# banner motd #
Enter TEXT message. End with the character "#".
Unauthorized access is strictly prohibited.#
```

## Hasła

Hasło dostępu do trybu uprzywilejowanego EXEC:
```
S1(config)# enable secret class
```

Hasło dostępu przez port konsoli:
```
S1(config)# line con 0
S1(config-line)#password cisco
S1(config-line)# login
S1(config-line)# exit
S1(config)#
```

Zapisz konfigurację (ustalone hasła będą obowiązywały po restarcie switcha)
```
S1# copy running-config startup-config
```

## Umożliwienie zdalnego zarządzania przełącznikiem
* przejście do trybu konfiguracji globalnej
* ustawienie adresu IP dla interfejsu SVI przełącznika
```
S1# config t
S1#(config)# interface vlan 1
S1(config-if)# ip address 192.168.1.2 255.255.255.0
S1(config-if)# no shut
S1(config-if)# exit
S1(config)#
```

* konfiguracja terminala wirtualnego (VTY) (wymagane do połączenia przez telenet)
```
S1(config)#line vty 0 4
S1(config-line)# password cisco
S1(config-line)# login
S1(config-line)# end
S1#
```

Nawiązywanie sesji telnet: w `Putty`: adres IP podany poprzez komendę `ip adress` wyżej, connection type: `Telnet`. Switch zapyta o hasło, takie jak ustawione wyżej (cisco).

## Inicjalizacja, resetowanie

Usunięcie pliku `vlan.dat` z pamięci flash
```
Switch# delete vlan.dat
```

Usunięcie konfiguracji startowej (usunięcie wszystkich plików konfiguracyjnych)
```
Switch# erase startup-config
```

Restart/przeładowanie switcha
```
Switch# reload
```