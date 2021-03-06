# Podstawy Automatyki i Robotyki W04
notatki na podstawie przykładowego testu zaliczeniowego

---

## Sterowanie predykcyjne
W sterowaniu predykcyjnym regulator dostosowuje swoje działanie z wyprzedzeniem, zanim nastąpią zmiany wielkości wyjściowych układu [[link]]
(https://pl.wikipedia.org/wiki/Sterowanie_predykcyjne)
![](https://upload.wikimedia.org/wikipedia/commons/c/c3/Schemat_dzialania_MPC.png)

## Regulatory PID
Ich celem jest utrzymanie wartości wyjściowej na określonym poziomie, zwanym wartością zadaną. [[link]](https://pl.wikipedia.org/wiki/Regulator_PID)

Przykład: chcemy żeby silnik miał stałe obroty, mimo stale zmieniających się czynników zewnętrznych (np. jego obciążenia). Regulator co chwilę sprawdza uchyb od pożądanej wartości, dostosowuje wartości mające wpływ na obroty silnika tak, żeby szybkość obrotów wróciła do normy.

Wejście regulatora: uchyb (różnica między wartością zadaną a wyjściem obiektu)

Wyjście: sygnał sterujący silnikiem

Algorytm obliczeń regulatora PID zawiera trzy oddzielne stałe parametry i dlatego czasami bywa nazywany regulatorem z trzema członami: proporcjonalnym, całkującym i różniczkującym, oznaczonymi odpowiednio P, I i D.

* P - zmienia wartość wyjścia mnożąc jakąś stałą przez wartość błędu. Nie wpływa na redukcję błędu (uchybu).
* I - dostosowuje wyjście do danych z przeszłości. Zmienia wartość wyjścia, jeżeli dotychczasowe zmiany nie dały pozytywnego rezultatu. Jego zadaniem jest sprowadzenie uchybu do zera.
* D - nie bierze pod uwagę wartości błędu lecz prędkość jego zmian. Dąży do ustabilizowania prędkości zmian, żeby uniknąć (overshooting?) ominięcia wartości do której dążyliśmy (z błędu dodatniego przeszliśmy w ujemny)

[Polecam ten artykuł na temat PID](https://en.wikipedia.org/wiki/PID_controller#Control_loop_example)

![](https://upload.wikimedia.org/wikipedia/commons/thumb/4/43/PID_en.svg/971px-PID_en.svg.png)
r(t) - wartość zadana, y(t) - wartość zmierzona

Wartości Kp, Ti oraz Td na obrazku to tzw. nastawy regulatorów. Dobiera się je w zależności od zastosowania regulatora.

## Horyzont predykcji 

Z jak dużym wyprzedzeniem model potrafi przewidzieć przyszłość.

## Histogramy brzegowe (lateralne)

## Klasa przegubu
(tutaj nie jestem pewien)

Ilość utraconych stopni swobody przegubu. To znaczy: przegub może mieć 6 stopni swobody (poruszać się w po osiach X, Y, Z i obracać się po osiach X, Y, Z). Przegub 5 klasy straciłby 5 opcji zmiany pozycji, tzn. mógłby się na przykład móc obracać tylko po osi X.
## Ruchliwość
Liczba stopni swobody łacucha kinematycznego z unieruchomionym pierwszym członem. Ruchliwość jest równa liczbie niezależnych napędów, które zapewniają określony ruch mechanizmu.

![](./notatki_zalaczniki/ruchliwosc.png)

Lub `r=w-6` gdzie `w` to liczba stopni swobody.

gdzie: n liczba członów; i klasa przegubu; pi liczba przegubów i-tej klasy

## Manewrowość
liczba stopni swobody łańcucha kinematycznego z unieruchomionym pierwszym i ostatnim członem

`m = r - 6`

## Przekaźnik elektromagnetyczny
> Dzięki przekaźnikom sygnały o większej amplitudzie, większym poziomie napięć lub prądów mogą wywoływać skutki w obwodach, w których obowiązują inne poziomy sygnałów.

![](https://upload.wikimedia.org/wikipedia/commons/f/fd/Przeka%C5%BAnik.GIF)

[źródło](https://pl.wikipedia.org/wiki/Przeka%C5%BAnik)

## Realizacja iloczynu logicznego dwóch zmiennych
[Iloczyn logiczny inaczej koniunkcja](https://pl.wikipedia.org/wiki/Koniunkcja_(logika))
![](./notatki_zalaczniki/and_relay.jpg)
[źródło](http://slideplayer.com/slide/8621835/)

## Układ otwarty

Układ automatyki w którym nie występuje sprzężenie zwrotne. Przebieg sygnału następuje tylko w jednym kierunku, tj. od wejścia do wyjścia. Stosowany w robotach I regeneracji, tj. takich, które nie mają czujników zewnętrznych.

## Regulator dwustawny
Regulator w którym sygnał przyjmuje wyłącznie 2 wartości. Prawdopodobnie stosuje się je do sterowania obiektami cieplnymi (ogrzewanie domu: zbyt zimno - włącz ogrzewanie, zbyt ciepło - wyłącz) ?

## Regualtor Watta
Stosowany w maszynach parowych, wykorzystuje siłę odśrodkową do regulacji prędkości obrotów. Ciężarki były wprawiane w ruch obrotowy wokół pewnej osi, im szybciej się obracały tym bardziej oddalały się od osi, co odcinało dopływ pary w maszynie parowej. Zwolnienie obrotów powodowało opadnięcie ciężarków i przywrócenie dopływu pary.
[wiki](https://pl.wikipedia.org/wiki/Regulator_od%C5%9Brodkowy_obrot%C3%B3w)

## Seperacja galwiniczna
Izolacja dwóch bloków systemu elektrycznego tak, aby prąd nie przepływał bezpośrednio z jednego bloku do drugiego (np. gdy części urządzenia pracują na różnych napięciach)

Przykładowe zastosowanie: transoptor. Transoptor może działać jako czujnik odbiciowy (wykrywający zmiany koloru podłoża), jedna część obwodu emituje światło, druga (oddzielona od pierwszej) odbiera je.

## Sterowanie odporne
Sposób sterowania zaprojektowany aby regulator działał poprawnie w warunkach gdy pewne informacje na temat obiektu są niepewne (np. parametry modelu są wyzanczone w przybliżony sposób). Sterowanie odporne potrzebuje infromacji o granicach niepewności pomiarów, gwarantuje, że jeżeli zmiany leżą w pewnych granicach to nie trzeba zmieniać przyjętej zasady sterowania.
[źródło](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&ved=0ahUKEwj-oPip-_PbAhXBZFAKHTHrAucQFgg5MAE&url=http%3A%2F%2Fanna.czemplik.staff.iiar.pwr.wroc.pl%2Fimages%2FDprojektowanie%2F09_Odporne.pdf&usg=AOvVaw1GZQIn86bCDI7inIZRD4Zp)

## System BIBO (Bounded Input Bounded Output)
Jedna z definicji stabilności układu dynamicznego.

Układ wejściowo-wyjściowy (tj. układ dynamiczny) jest BIBO stabilny jeżeli ograniczonemu sygnałowi wejściowemu u(t), odpowiada ograniczony sygnał wyjściowy y(t).

[wiki](https://pl.wikipedia.org/wiki/BIBO_stabilno%C5%9B%C4%87)

## Robot sferyczny
Podział robotów ze względu na ich strukturę kinematyczną można zobaczyć tutaj:
http://www.asimo.pl/teoria/roboty-przemyslowe.php

## Robot PR02
robot prosty, pozycjonowany zderzakowo

## Cobot
Robot zaprojektowany do interakcji z człowiekiem. W odróżnieniu od innych robotów przemysłowych, posiada on zestaw sensorów pozwalająch mu wykryć nieprzewidziane sytuacje w jego środowisku pracy.

## Proste zadanie kinematyki
Zadanie kinematyki prostej można określić następująco: posiadając dane o zmiennych przegubowych należy określić pozycję i orientację końcówki roboczej.

[Przykładowe zadania z rozwiązaniami](https://www.robotyka.com/teoria.php/teoria.75)

## Rezolwer
Urzędzenie służące do pomiaru kąta [[źródło]](https://pl.wikipedia.org/wiki/Resolver). Uzyskuje informacje o położeniu kątowym przegubu.

## Enkoder
Służy do uzyskiwania informacji na temat prędkości i kierunku obrotu koła

## Sposoby detekcji uszkodzeń
?

## Liczba stopni swobody (degrees of fredom)(DoF)
Najmniejsza liczba niezależnych zmiennych potrzebnych do jednoznaczego opisania stanu układu
![](https://upload.wikimedia.org/wikipedia/commons/thumb/8/88/Brosen_shipsmovemensonthewave.svg/567px-Brosen_shipsmovemensonthewave.svg.png)

The six degrees of freedom of movement of a ship [[źródło]](https://en.wikipedia.org/wiki/Degrees_of_freedom_(mechanics))


## System statyczny
wyjście zależy jedynie od wejścia (przykład z wykładu: włącznik światła)

## System dynamiczny
wyjście może zależeć od wartości wejścia w chwilach innych niż t0 (przykład z wykładu: żelazko nie jest gorące od razu po włączeniu, tak samo nie wychładza się natychmiast to odłączeniu prądu)

## System stacjonarny
Dla każdego t0 i identycznych warunków początkowych otrzymujemy to samo u(t-t0)

## System liniowy
System który spełnia zasadę superpozycji (?)
1) dla dowolnych pobudzen u1(t) i u2(t) odpowiedź na sumę u1(t)+u2(t) jest równa sumie odpowiedzi y1(t)+y2(t)
2) odpowiedź na pobudzenie a*u1(t) jest równa a*y1(t) dla dowolnego a

Przykład z wykładu: orkiestra i skrzypek; jeżeli nagranie ich osobno da taki sam efekt co gdyby grali razem jednocześnie, to taki system jest liniowy)

## Enkoder magnetyczny
Urządzenie służące do uzyskania informacji na temat prędkości i obrotu koła

![](./notatki_zalaczniki/magneticencoder.jpg)

## Odometria
Dział miernictwa, który zajmuje się pomiarem odległości. W robotyce jest wykorzystywana do oszacowania zmiany położenia robota względem początkowej pozycji.

> Suppose a robot has rotary encoders on its wheels or on its legged joints. It drives forward for some time and then would like to know how far it has traveled. It can measure how far the wheels have rotated, and if it knows the circumference of its wheels, compute the distance.
[źródło](https://en.wikipedia.org/wiki/Odometry)

## Termopara (termoelement)
> Termopara składa się z pary różnych metali zwykle w postaci przewodów, spojonych na obu końcach. Jedno złącze umieszczane jest w miejscu pomiaru, podczas gdy drugie utrzymywane jest w stałej temperaturze odniesienia (np. mieszanina wody z lodem). Gdy nie jest wymagana duża dokładność (dopuszczalny błąd rzędu kilku stopni), jako temperaturę odniesienia traktuje się np. temperaturę wnętrza szafy sterowniczej maszyny przemysłowej, mierzoną z pomocą innego czujnika (jest to tzw. sztuczne zero). Pod wpływem różnicy temperatury między złączami (pomiarowym i odniesienia) powstaje różnica potencjałów (siła elektromotoryczna), zwana w tym przypadku siłą termoelektryczną, proporcjonalna do różnicy temperatur. [źródło](https://pl.wikipedia.org/wiki/Termopara)

## PLC
Programowalny sterownik logiczny (programmable logic controller). Uniwersalne urządzenie przeznaczone do sterowania pracą maszyny.

> Na ogół to sterowniki PLC połączone są bezpośrednio z urządzeniami wykonawczymi (zawory, pompy itp.) i pomiarowymi (czujniki temperatury, poziomu itp.) i zbierają aktualne dane z obiektu oraz wykonują automatyczne algorytmy sterowania i regulacji. Za pośrednictwem sterowników PLC dane trafiają do systemu komputerowego i tam są archiwizowane oraz przetwarzane na formę bardziej przyjazną dla użytkownika. [źródło](https://pl.wikipedia.org/wiki/SCADA)

## SCADA
![](https://upload.wikimedia.org/wikipedia/commons/8/88/Scada_std_anim_no_lang.gif)

System informatyczny pełniący rolę nadrzędną do sterowników PLC. Zbiera dane pomiarowe, steruje procesem, wizualizuje je, archiwizuje dane oraz alarmuje wykrywając nieprawidłowości.

## Lidary
Laserowe, trójwymiarowe czujniki odległości. Umożliwiają bezpośredni odczyt mierzonej odległości we współrzędnych trójwymiarowych, co stanowi kolosalną oszczędność kosztów przetwarzania danych. W porównaniu do układów wizyjnych, Lidary są niewrażliwe na wpływy iluminacji zewnętrznej (np. eliminuje to konieczność odróżniania cieni od rzeczywistych obiektów).

## Czujnik taktylny
Czujnik dotykowy, realizujący pomiar w bezpośrednim kontakcie z bodźcem źródła fizycznego. Może to być binarny czujnik obecności lub też analogowy czujnik siły nacisku.
