# Maze Game

- [Maze Game](#maze-game)
  - [Krótki opis](#krótki-opis)
  - [Funkcjonalność](#funkcjonalność)
    - [Rozgrywka](#rozgrywka)
    - [Wizualizacja](#wizualizacja)
    - [Interfejs](#interfejs)
  - [Implementacja](#implementacja)
    - [Backend](#backend)
    - [Frontend](#frontend)
  - [Wykorzystane technologie](#wykorzystane-technologie)
    - [Zależności](#zależności)
  - [Proces budowania](#proces-budowania)
  - [Działanie aplikacji](#działanie-aplikacji)

## Krótki opis

> Gra generująca labirynty o rosnącym rozmiarze, które użytkownik musi rozwiązać w ograniczonym czasie / ruchach.

## Funkcjonalność

### Rozgrywka

- Poruszanie się za pomocą strzałek lub WSAD
- Labirynt będzie zwiększał swoje rozmiary oraz nakładał surowsze ograniczenia wraz z każdym rozwiązaniem
- Poziom trudności
  - obliczany na podstawie najmniejszej liczby ruchów potrzebnych na rozwiązanie labiryntu (wyliczonych przez algorytm)
  - limit ruchów
  - limit czasowy

### Wizualizacja

- Wizualizacja labiryntu w 3d
- Podświetlenie przebytej trasy
- W przypadku przegranej możliwość wyświetlenia optymalnego rozwiązania - np. podświetlenie trasy - z obecnego położenia oraz od początku labiryntu + liczba potrzebnych ruchów

### Interfejs

- Opcja wyboru algorytmu generacji labiryntu
- Opcja wyboru algorytmu znajdowania rozwiązania
- Opcja wyboru avatara

## Implementacja

### Backend

- #### Implementacja algorytmów do generowania labiryntów

  - [Aldous-Broder](https://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm.html)
  - [Eller's](https://weblog.jamisbuck.org/2010/12/29/maze-generation-eller-s-algorithm.html)
  - [Growing Tree](http://weblog.jamisbuck.org/2011/1/27/maze-generation-growing-tree-algorithm)
  - [Hunt and Kill](https://weblog.jamisbuck.org/2011/1/24/maze-generation-hunt-and-kill-algorithm.html)
  - [Kruskal's](https://weblog.jamisbuck.org/2011/1/3/maze-generation-kruskal-s-algorithm.html)
  - [Prim's](http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm)
  - [Recursive Backtracking](http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking)
  - [Recursive Division](https://weblog.jamisbuck.org/2011/1/12/maze-generation-recursive-division-algorithm.html)
  - [Sidewinder](https://weblog.jamisbuck.org/2011/2/3/maze-generation-sidewinder-algorithm.html)
  - [Wilson's](https://weblog.jamisbuck.org/2011/1/20/maze-generation-wilson-s-algorithm.html)

- #### Implementacja algorytmów do znajdywania rozwiązań

  - [A\*](https://en.wikipedia.org/wiki/A*_search_algorithm)
  - [Breadth first search](https://en.wikipedia.org/wiki/Breadth-first_search)
  - [Djikstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

### Frontend

---

## Wykorzystane technologie

### Zależności

- Buildsystem [**CMake**](https://cmake.org)
- Generator [**Ninja**](https://ninja-build.org)
- [**git**](https://git-scm.com)
- Kompilator [**GCC**](https://www.mingw-w64.org/downloads/#mingw-builds)
- Testy [**GoogleTest**](https://github.com/google/googletest) - jako submodule
- [**VCPKG**](https://vcpkg.io/en/getting-started.html) za pomocą komendy:
- Formatowanie - użycie `clang-format` stylu _Chromium_

  Wymaga zmiany ścieżek w `src/graphics/CMakeLists.txt` na odpowiednie

## Proces budowania

1. Instalacja [zależności](#zależności)
2. Sklonowanie repozytorium

   ```git
     git clone -b master https://github.com/wstyczen/MazeGame/blob/Graphics/src/graphics/CMakeLists.txt
   ```

3. Instalacja bibliotek _glfw_, _glm_ oraz _glad_ przy pomocy _VCPKG_

- Użycie komendy

  ```sh
    ./vcpkg install glfw3 glad glm --triplet=--triplet=x64-mingw-dynamic
  ```

- Oraz zmiana ścieżek w `src/graphics/CMakeLists.txt` na odpowiadające instalacji

  ```cmake
    set(glad_DIR "<path_to_glad>")
    set(glm_DIR "<path_to_glm>")
    set(glfw3_DIR "<path_to_glfw>")
  ```

4. Wywołanie skryptu `build.sh` z repozytorium

   ```sh
     ./build.sh
   ```

## Działanie aplikacji
