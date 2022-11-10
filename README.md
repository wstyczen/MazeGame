# Maze Game

- [Maze Game](#maze-game)
  - [Założenia wstępne](#założenia-wstępne)
    - [Krótki opis](#krótki-opis)
    - [Funkcjonalność](#funkcjonalność)
      - [Rozgrywka](#rozgrywka)
      - [Wizualizacja](#wizualizacja)
      - [Interfejs](#interfejs)
    - [Implementacja](#implementacja)
      - [Backend](#backend)
      - [Frontend](#frontend)
    - [Dodatkowe funkcjonalności](#dodatkowe-funkcjonalności)

## Założenia wstępne

### Krótki opis

> Gra generująca labirynty o rosnącym rozmiarze i trudności, które użytkownik musi rozwiązać w ograniczonym czasie / ruchach.

### Funkcjonalność

#### Rozgrywka

- Poruszanie się za pomocą strzałek lub WSAD
- Labirynt będzie zwiększał swoje rozmiary oraz nakładał surowsze ograniczenia wraz z każdym rozwiązaniem
- Poziom trudności
  - obliczany na podstawie najmniejszej liczby ruchów potrzebnych na rozwiązanie labiryntu (wyliczonych przez algorytm)
  - limit ruchów
  - limit czasowy

#### Wizualizacja

- Wizualizacja labiryntu w 2d
- Dodatkowa wizualizacja pozycji - podświetlenie zajętego pola / podświetlenie rzędu i kolumny
- W przypadku przegranej możliwość wyświetlenia optymalnego rozwiązania - np. podświetlenie trasy - z obecnego położenia oraz od początku labiryntu + liczba potrzebnych ruchów

#### Interfejs

- Opcja wyboru algorytmu generacji labiryntu
- Opcja wyboru algorytmu znajdowania rozwiązania
- Opcja wyboru avatara
- Opcja dostosowania kolorów avatara, ścian labiryntu, itd.
- Opcja zapisu oraz odczytu mapy
- Opcja zapisu ustawień

### Implementacja

> Wykorzystanie narzędzia _**Cmake**_ oraz systemu kompilacji **Ninja**

#### Backend

> Napisany w **C++** (**gcc**), z wykorzystaniem bibliotek **_Boost_** oraz **_GoogleTest_**

- ##### Implementacja algorytmów do generowania labiryntów

  - Zaimplementowane:
    - [Aldous-Broder](https://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm.html)
    - [Eller's](https://weblog.jamisbuck.org/2010/12/29/maze-generation-eller-s-algorithm.html)
    - [Growing Tree](http://weblog.jamisbuck.org/2011/1/27/maze-generation-growing-tree-algorithm)
    - [Hunt and Kill](https://weblog.jamisbuck.org/2011/1/24/maze-generation-hunt-and-kill-algorithm.html)
    - [Kruskal's](https://weblog.jamisbuck.org/2011/1/3/maze-generation-kruskal-s-algorithm.html)
    - [Prim's](http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm)
    - [Recursive Backtracking](http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking)
    - [Sidewinder](https://weblog.jamisbuck.org/2011/2/3/maze-generation-sidewinder-algorithm.html)
    - [Wilson's](https://weblog.jamisbuck.org/2011/1/20/maze-generation-wilson-s-algorithm.html)
  - TODO:
    - [Recursive Division](https://weblog.jamisbuck.org/2011/1/12/maze-generation-recursive-division-algorithm.html)

- ##### Implementacja algorytmów do znajdywania rozwiązań

  - Zaimplementowane:
    - [A\*](https://en.wikipedia.org/wiki/A*_search_algorithm)
    - [Breadth first search](https://en.wikipedia.org/wiki/Breadth-first_search)
    - [Djikstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
  - TODO:
    - [Greedy Best-First-Search](https://en.wikipedia.org/wiki/Best-first_search)

#### Frontend

> Z wykorzystaniem biblioteki **OpenGL** lub podobnych bibliotek, np **SDL**

---

### Dodatkowe funkcjonalności

> Poniższe funkcjonalności zostaną zaimplementowane jedynie jeśli ograniczenia czasowe na to pozwolą

- Dodanie bardziej skomplikowanej animacji pojawienia się labiryntu oraz ruchu
- Wybór poziomu trudności - różne wymagania czasowe i maksymalna liczba ruchów
- Dodatkowe opcje trudności, np:
  - niewidoczne ściany - część ścian jest niewidoczna, pojawiają się dopiero gdy gracz próbuję przejść przez to pole
  - labirynt zmienia się podczas rozgrywki - gracz jest chwilowo unieruchomiony, a labirynt zmienia postać (miejsce położenia gracza musi pozostać puste, pozostałe ruchy/czas są odświerzane)
  - błędne ruchy się liczą - próba poruszenia się w kierunku zablokowanym przez ścianę jest wliczana do limitu ruchów
