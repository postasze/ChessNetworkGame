# Chess network game
Sieciowa gra w szachy wykorzystująca sieciowe API BSD Sockets

Aplikacja MMO w której wielu graczy może tworzyć stoły szachowe i dołączać do istniejących stołów szachowych

Aplikacja działa w trybie klient - serwer, jest jeden proces serwera i wiele procesów klientów

Dokumentacja aplikacji znajduje się w folderze docs

Screeny z działania aplikacji znajdują się w folderze screens

1. Instrukcja kompilacji i instalacji aplikacji

1.1 Aplikacja została stworzona z użyciem bibliotek Qt, więc trzeba pobrać biblioteki Qt z internetu np. poprzez instalację środowiską Qt stąd https://www.qt.io/download

1.2 Następnie trzeba rozpakować plik zip zawierający kod źródłowy aplikacji

1.3 Potem trzeba przejść w konsoli bash lub cmd do folderu ChessNetworkGameServer, w którym jest zawarty plik ChessNetworkGameServer.pro

1.4 Następnie trzeba wywołać polecenie qmake, które generuje automatycznie plik Makefile (w windowsie jeśli nie została ustawiona zmienna środowiskowa QMAKE konieczne jest wpisanie całej ścieżki do programu qmake, typu C:\Qt\5.10.0\mingw53_32\bin\qmake.exe)

1.5 Potem trzeba wywołać polecenie make, które generuje automatycznie działającą aplikację (w windowsie jeśli nie została ustawiona zmienna środowiskowa MAKE konieczne jest wpisanie całej ścieżki do programu make, typu C:\Qt\Tools\mingw530_32\bin\mingw32-make.exe)

1.6 Następnie można już uruchomić aplikację z pliku ChessNetworkGameServer.exe, np. poprzez polecenie ./ChessNetworkGameServer (w windowsie może być konieczne ustawienie ścieżki do bibliotek Qt w zmiennych środowiskowych lub przekopiowanie bibliotek Qt do folderu w którym znajduje się plik exe, biblioteki Qt znajdują się w ścieżce typu C:\Qt\Tools\QtCreator\bin)

1.7 Te same kroki 3, 4, 5 trzeba wykonać dla ChessNetworkGameClient, bo aplikacja składa się z dwóch projektów Qt uruchamianych oddzielnie (serwer, klient)

Kompilacja aplikacji w systemie Linux powinna przebiegać o wiele sprawniej i prościej niż w systemie Windows. 
Alternatywnie można też uruchomić aplikację wewnątrz środowiska Qt

2. Instrukcja uruchamiania aplikacji

Aplikacja sprawnie działa na linuxie Ubuntu, nie testowano działania na windowsie

Aplikację można uruchamiać na wielu komputerach podłączonych do tej samej sieci bezprzewodowej lub przewodowej,
przy czym proces serwera powinien być uruchomiony na jednym komputerze a procesy klientów na pozostałych komputerach

Aplikację można też uruchomić na jednym komputerze poprzez uruchomienie na nim wszystkich procesów

2.1 Najpierw uruchamiamy projekt ChessNetworkGameServer (1 proces serwera), który powinien wyświetlić w konsoli numer portu w sieci

2.2 Następnie uruchamiamy projekty ChessNetworkGameClient (2 lub więcej procesów klientów) podając 2 argumenty: adres IP serwera w sieci i port serwera (podany przez proces serwera)
np. ./ChessNetworkGameClient adres_ip_serwera port_serwera

2.3 jeśli uruchamiamy aplikację na wielu komputerach to jako adres ip podajemy adres ip komputera w sieci, na którym uruchomiony jest proces serwera

Adres ten można pobrać komendą ifconfig na linuxie lub ipconfig na windowsie

jeśli uruchamiamy wszystkie procesy na jednym komputerze to możemy jako adres ip podać 127.0.0.1 (localhost)
np. ./ChessNetworkGameClient 127.0.0.1 51623

3. Dodatkowe informacje

Serwer ma główny wątek do łączenia się z nowymi klientami i używa wielu wątków posix thread do obsługi wielu podłączonych klientów, jeden wątek dla każdego klienta
każdy klient ma główny wątek oraz wątek posix reagujący na komunikaty z serwera