# Chess network game
Sieciowa gra w szachy wykorzystująca sieciowe API BSD Sockets

Instrukcja instalacji i uruchamiania aplikacji

1.1 Aplikacja została stworzona z użyciem bibliotek Qt, więc trzeba pobrać biblioteki Qt z internetu np. poprzez instalację środowiską Qt stąd https://www.qt.io/download

1.2 Następnie trzeba rozpakować plik zip zawierający kod źródłowy aplikacji

1.3 Potem trzeba przejść w konsoli bash lub cmd do folderu ChessNetworkGame, w którym jest zawarty plik ChessNetworkGame.pro

1.4 Następnie trzeba wywołać polecenie qmake, które generuje automatycznie plik Makefile (w windowsie jeśli nie została ustawiona zmienna środowiskowa QMAKE konieczne jest wpisanie całej ścieżki do programu qmake, typu C:\Qt\5.10.0\mingw53_32\bin\qmake.exe)

1.5 Potem trzeba wywołać polecenie make, które generuje automatycznie działającą aplikację (w windowsie jeśli nie została ustawiona zmienna środowiskowa MAKE konieczne jest wpisanie całej ścieżki do programu make, typu C:\Qt\Tools\mingw530_32\bin\mingw32-make.exe)

1.6 Następnie można już uruchomić aplikację z pliku ChessNetworkGame.exe (w windowsie może być konieczne ustawienie ścieżki do bibliotek Qt w zmiennych środowiskowych lub przekopiowanie bibliotek Qt do folderu w którym znajduje się plik exe, biblioteki Qt znajdują się w ścieżce typu C:\Qt\Tools\QtCreator\bin)

Kompilacja aplikacji w systemie Linux powinna przebiegać o wiele sprawniej i prościej niż w systemie Windows. Alternatywnie można też uruchomić aplikację wewnątrz środowiska Qt
