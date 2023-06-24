# Baza danych biblioteki

## Uruchamiania aplikacji

### Aby uruchomić aplikacje należy mieć zainstalowany kompilator g++.

#### Windows

```shell
g++ src/*.cpp -o LibraryManagementSystem.exe
LibraryManagementSystem.exe
```

#### Linux/Mac Os
```shell
g++ src/*.cpp -o LibraryManagementSystem
./LibraryManagementSystem
```

## Opis
Ta aplikacja jest prostym systemem zarządzania biblioteką. Pozwala na dodawanie i usuwanie książek, dodawanie i usuwanie czytelników, wypożyczanie i zwracanie książek oraz wyświetlanie informacji o dostępnych książkach i czytelnikach.

## Funkcje
### Aplikacja oferuje następujące funkcje:

**1.Dodaj książkę:** Pozwala na dodanie nowej książki do biblioteki. Podczas dodawania należy podać tytuł, autora i ilość egzemplarzy książki.

**2.Usuń książkę:** Pozwala na usunięcie książki z biblioteki. Wymaga podania tytułu i autora usuwanej książki.

**3.Dodaj czytelnika:** Pozwala na dodanie nowego czytelnika do biblioteki. Podczas dodawania należy podać imię, nazwisko i adres e-mail czytelnika.

**4.Usuń czytelnika:** Pozwala na usunięcie czytelnika z biblioteki. Wymaga podania imienia i nazwiska lub adresu e-mail czytelnika.

**5.Wypożycz książkę:** Pozwala na wypożyczenie książki przez czytelnika. Wymaga podania tytułu i autora wypożyczanej książki oraz imienia i nazwiska lub adresu e-mail czytelnika.

**6.Zwróć książkę:** Pozwala na zwrot wypożyczonej książki przez czytelnika. Wymaga podania tytułu i autora zwracanej książki oraz imienia i nazwiska lub adresu e-mail czytelnika.

**7.Wyświetl wszystkie książki:** Wyświetla listę wszystkich książek znajdujących się w bibliotece.

**8.Wyświetl dostępne książki:** Wyświetla listę dostępnych książek, które można wypożyczyć.

**9.Wyświetl wszystkich czytelników:** Wyświetla listę wszystkich czytelników zarejestrowanych w bibliotece.

**10.Wyświetl książki wypożyczone przez czytelnika:** Wyświetla listę książek wypożyczonych przez określonego czytelnika. Wymaga podania imienia i nazwiska lub adresu e-mail czytelnika.

**11.Zakończ program:** Zapisuje dane biblioteki do pliku i kończy działanie aplikacji.

## Plik 'library.txt'
Dane o książkach, czytelnikach i wypożyczonych książkach są zapisywane do pliku **'library.txt'** przy zakończeniu działania aplikacji. Przy uruchomieniu aplikacji, dane są wczytywane z tego pliku.

## Klasy i struktury danych
Aplikacja korzysta z następujących klas i struktur danych:

**Book:** Klasa reprezentująca książkę, zawierająca informacje o tytule, autorze i liczbie egzemplarzy.

**BookLinkedList:** Struktura danych w postaci listy jednokierunkowej, służąca do przechowywania książek.

**BorrowedBooksLinkedList:** Struktura danych w postaci listy jednokierunkowej, służąca do przechowywania wypożyczonych książek.

**Console:** Klasa zawierająca namespace wraz z funkcjami do czyszczenia konsoli, czekania na wciśnięcia klawisza przez użytkownika oraz wyświetlania informacji o powodzeniu bądź nie powodzeniu.

**Library:** Klasa reprezentująca bibliotekę, zawierająca listy książek, czytelników i wypożyczonych książek.

**Reader:** Klasa reprezentująca czytelnika, zawierająca informacje o imieniu, nazwisku i adresie e-mail.

**ReaderDoubleLinkedList:** Struktura danych w postaci listy dwukierunkowej, służąca do przechowywania czytelników.

### Wykonane przez:
**Maciej Deroń**

**Mariusz Ignaciuk**