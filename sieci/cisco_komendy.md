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

Adresy MAC dla każdego interfejsu na routerze:
```
R1> show arp
Protocol  Address          Age (min)  Hardware Addr   Type   Interface
Internet  192.168.1.1             -30f7.0da3.1821  ARPA   GigabitEthernet0/1
```

Szczegółowe informacje o interfejsie (podejrzenie adresu MAC portu?)
```
R1> show interfaces g0/1
GigabitEthernet0/1 is up, line protocol is up
Hardware is CN Gigabit Ethernet, address is 30f7.0da3.1821(bia 30f7.0da3.1821)
Internet address is 192.168.1.1/24
MTU 1500 bytes, BW 100000 Kbit/sec, DLY 100 usec,
reliability 255/255, txload 1/255, rxload 1/255
Encapsulation ARPA, loopback not set
```

Podejrzenie wszystkich adresów MAC na switchu
```
Switch> showmac address-table
```

Wpisy ARP w przełączniku
```
S1# show ip arp
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
Zapobieganie niepożądanym zapytaniom DNS (zapobiegnięcie próbom tłumaczenia niepoprawnie  wprowadzonych poleceń na nazwy hostów)(DNS-lookup)
```
S1(config)# no ip domain-lookup
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

Hasło do VTY
> Virtual teletype (VTY) is a command line interface (CLI) created in a router and used to facilitate a connection to the daemon via Telnet, a network protocol used in local area networks.
```
R1(config)# line vty 0 4
R1(config-line)# password cisco
R1(config-line)# login
R1(config-line)# exit
R1(config)#
```

Zaszyfruj hasła
```
R1(config)# service password-encryption
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

* konfiguracja terminala wirtualnego (VTY) (wymagane do połączenia przez telnet)
```
S1(config)#line vty 0 4
S1(config-line)# password cisco
S1(config-line)# login
S1(config-line)# end
S1#
```

Nawiązywanie sesji telnet: w `Putty`: adres IP podany poprzez komendę `ip adress` wyżej, connection type: `Telnet`. Switch zapyta o hasło, takie jak ustawione wyżej (cisco).

## Interfejsy

Aktywacja i konfiguracja interfejsów na routerze.
Przypisanie interfejsom adresów IP
```
R1(config)# int g0/0
R1(config-if)# description Connection to PC-B.
R1(config-if)# ip address 192.168.0.1 255.255.255.0
R1(config-if)# no shut
R1(config-if)#
```
Zapis konfiguracji
```
R1# copy running-config startup-config
```

## Inicjalizacja, resetowanie

Usunięcie pliku z definicją sieci VLAN. Usunięcie pliku `vlan.dat` z pamięci flash
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

Reset tablicy adresów MAC:
```
S2# clear mac address-table dynamic
```

# Windows

Wyświetlenie wpisów ARP na komputerze:
```
arp –a
```

Usunięcie wszystkich wpisów bufora ARP z komputera:
```
arp –d *
```

Tablica routingu (tablica trasowania)
```
netstat -r
```

> Tablica trasowania – spis wskazujący, przez które sąsiadujące z routerem węzły sieci prowadzi trasa do węzłów oddalonych. Tablica trasowania jest utrzymywana niezależnie przez każdy router. 

> Mając informację o docelowym adresie IP router wybiera najlepiej pasujący wpis w tablicy. Ta zasada zwana jest LONGEST PREFIX MATCH, czyli zasadą najlepiej dopasowanego wpisu, a więc wpisu o najdłuższej pasującej kombinacji maski sieci i adresu docelowego. To oznacza, że w naszym przypadku wpis: 192.168.1.20/32 jest bardziej dopasowany niż 192.168.1.0/24 w poszukiwaniu trasy do adresu IP 192.168.1.20.
[źródło](https://bootcamp.grandmetric.com/aktualnosci/2018/03/01/dziala-tablica-routingu/)

* Lista interfejsów -  Zawiera adres MAC (ang. Media Access Control) wraz z przydzielonym przez system numerem dla każdego interfejsu sieciowego skonfigurowanego na hoście. Dotyczy to interfejsów Ethernet, Wi-Fi oraz adapterów Bluetooth.
* Tabela tras IPv4 - Zawiera listę wszystkich znanych przez hosta tras IPv4, w tym również bezpośrednich połączeń, sieci lokalnej i lokalnych tras domyślnych.
* Tabela tras IPv6 - Zawiera listę wszystkich znanych przez hosta tras IPv6, w tym również bezpośrednich połączeń, sieci lokalnej i lokalnych tras domyślnych.

```
netstat -a
```
> służy do wyświetlania wszystkich aktywnych połączeń protokołu TCP, a także portów protokołu TCP i UDP, na których komputer nasłuchuje. 