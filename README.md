# Maze Game

- [Maze Game](#maze-game)
  - [Krótki opis](#krótki-opis)
  - [Funkcjonalność](#funkcjonalność)
    - [Rozgrywka](#rozgrywka)
    - [Wizualizacja](#wizualizacja)
    - [Opcje](#opcje)
  - [Co nie zostało zrealizowane z założeń wstępnych](#co-nie-zostało-zrealizowane-z-założeń-wstępnych)
  - [Szczegóły implementacyjne](#szczegóły-implementacyjne)
    - [Backend](#backend)
    - [Frontend - _src/maze/graphics/_](#frontend---srcmazegraphics)
  - [Wykorzystane technologie](#wykorzystane-technologie)
    - [Zależności - konieczne to zbudowania projektu](#zależności---konieczne-to-zbudowania-projektu)
    - [Inne](#inne)
  - [Proces budowania](#proces-budowania)
  - [Fakty dotyczące projektu](#fakty-dotyczące-projektu)
    - [Liczba linii kodu](#liczba-linii-kodu)
    - [Napotkane problemy](#napotkane-problemy)

## Krótki opis

> Gra generująca labirynty o rosnącym rozmiarze, które użytkownik musi rozwiązać w ograniczonym czasie / ruchach.

## Funkcjonalność

### Rozgrywka

- Poruszanie się za kostką za pomocą strzałek po wygenerowanym labiryncie
- Labirynt zwiększa swoje rozmiary oraz nakłada surowsze ograniczenia wraz z każdym rozwiązaniem
- Poziom trudności
  > Obliczany na podstawie najmniejszej liczby ruchów potrzebnych na rozwiązanie labiryntu (wyliczonych przez solver)
  - limit ruchów
  - limit czasowy
- W razie wygranej zostaje wygenerowany kolejny labirynt o większym rozmiarzw
- W razie przegranej powrót do bazowego rozmiaru labiryntu

### Wizualizacja

- Animacja pojawiania się i znikania labiryntu
- Animacja ruchu
- Podświetlenie celu
- Podświetlenie przebytej trasy na bieżąco
- W przypadku przegranej wyświetlenie optymalnej trasy do rozwiązania z obecnego położenia

### Opcje

- Opcja wyboru poziomu trudności - _Easy_, _Normal_, _Hard_
- Opcja wyboru algorytmu generacji labiryntu
- Opcja wyboru algorytmu znajdowania rozwiązania
- Opcja wyboru ścieżki

## Co nie zostało zrealizowane z założeń wstępnych

- Interfejs użytkownika
  > Planowaliśmy zaimplementować interfejs użytkownika (_GUI_) - ie. w postaci przycisków do zmiany opcji rozgrywki.\
  > Główny powód - biblioteki, które wykorzystaliśmy wcześniej do wyświetlenia okienka nie dostarczają funkcjonalności do tworzenia _GUI_
- Wyświetlanie pozostałych ruchów i czasu w okienku gry\
  Biblioteki, które wykorzystaliśmy wcześniej do wyświetlenia okienka (GLFW) nie dostarczają prostej funkcjonalności do wyświetlania tekstu.\
  Próbowaliśmy wykorzystać do tego bibliotekę _Freetype_, ale nie było to proste
- Inne awatary - została zaimplementowana jedynie kostka o dowolnym kolorze\
  Implementacja ruchu dla zupełnie innego obiektu była dosyć skomplikowana

> Głównym powodem braku realizacji powyższych założeń był oczywiście brak czasu.

---

## Szczegóły implementacyjne

### Backend

- #### Implementacja algorytmów do generowania labiryntów - _/src/maze/generators/_

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

- #### Implementacja algorytmów do znajdywania rozwiązań - _src/maze/solvers/_

  - [A\*](https://en.wikipedia.org/wiki/A*_search_algorithm)
  - [Breadth first search](https://en.wikipedia.org/wiki/Breadth-first_search)
  - [Djikstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

> Algorytmy zostały zaimplementowane na podstawie opisu słownego, więc ich implementacja może się znacząco różnić od przykładowego kodu zamieszczonego na stronach, które zostały przytoczone.

- #### Interfejs gry - _src/maze/game/_

  > Interfejs do kontroli gry, wykorzystywany do komunikacji z interfejsem graficznym

### Frontend - _src/maze/graphics/_

 - Do wyświetlania kształtów zostały wykorzystane poniższe biblioteki: GLAD, GLFW3, GLM, które posłużyły zarówno do gospodarowania danymi jak ich przekształcania oraz ostatecznie publikowania obrazów na ekranie, dodatkowo klasy gospodarujące danymi takie jak VBO, VAO, EBO czy Shader zostały skopiowane z kursu OpenGL (https://github.com/VictorGordan/opengl-tutorials)
 - Każda złożona figura geometryczna dziedziczy po klasie bazowej SolidFigure, która udostępnia potrzebne metody do wyświetlania obiektów, to ona odpowiada za komunikację z klasami VBO, VAO, EBO, dlatego posiada ona wskaźniki na ich obiekty. Klasa SolidFigure posiada również macierze Model, View, Projection (MVP) 4x4 (klasa glm::mat4) odpowiadające za translacje wierzchołków brył w przestrzeni. Aby niepotrzebnie nie tworzyć głębokiej kopii obiektów klasy SolidFigure za każdym razem gdy zostaje użyty konstruktor kopiujący, zostały zastosowane sprytne wskaźniki std::shared_ptr, które dbają o czas życia danych kryjących się za obiekatmi VAO, VBO, EBO, pozwala to na wielokrotne wykorzystanie tych samych wierzchołków, które po przekształceniu przez macierze MVP skutkują różnymi figurami wyświetlanymi na ekranie.
 - Klasa DynamicSolidFigure stanowi rozszerenie funkcjonalne klasy SolidFigure o metody umożliwiające poruszanie bryłą, a w praktyce modyfikacje macierzy MVP.
 - Klasy MazeFigure oraz ComplexCube dziedziczą publicznie po klasie DynamicSolidFigure. Prezentują one odpowiednio labirynt oraz pionek w postaci kostki. Oferują one między innymi swoje specyficzne animacje, które zostały użyte w rozgrywce MazeGame.
 - Ostateczną klasą jest GameWindow, która łączy ze sobą wszystkie figury oraz obiekty potrzebne do wyświetlania ich na ekranie, dodatkowo posiada ona ustawienia, które odpowiadają za m.in. kolory figur i ich rozmiary.

## Wykorzystane technologie
- GLAD, GLFW3, GLM
### Zależności - konieczne to zbudowania projektu

- Wymagana wcześniejsza instalacja
  - _Buildsystem_ [**CMake**](https://cmake.org)
  - Generator [**Ninja**](https://ninja-build.org)
  - _Version control_ [**git**](https://git-scm.com)
  - Kompilator [**GCC**](https://www.mingw-w64.org/downloads/#mingw-builds)
  - [**VCPKG**](https://vcpkg.io/en/getting-started.html)
- Instalacja przed budowaniem
  - Biblioteki do [**OpenGL**](https://www.opengl.org)
    > Instalacja opisana w [proces budowania](#proces-budowania)
  - Testing [**GoogleTest**](https://github.com/google/googletest) - jako submodule git

### Inne

- Formatowanie kodu - użycie `clang-format` stylu _Chromium_
- IDE - [VSCode](https://code.visualstudio.com)
  - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
  - [Microsoft C/C++](https://code.visualstudio.com/docs/languages/cpp)
  - [Google Test Adapter](https://marketplace.visualstudio.com/items?itemName=DavidSchuldenfrei.gtest-adapter)

## Proces budowania

1. Sprawdzanie czy zainstalowane są wszystkie [zależności](#zależności---konieczne-do-zbudowania-projektu)
2. Sklonowanie i przejście do repozytorium

   ```bash
     git clone https://github.com/wstyczen/MazeGame.git
     cd MazeGame/
   ```

3. Instalacja bibliotek _glfw_, _glm_ oraz _glad_ przy pomocy _VCPKG_

   - Użycie komendy

     ```sh
       ./vcpkg install glfw3 glad glm --triplet=--triplet=x64-mingw-dynamic
     ```

   - Oraz zmiana ścieżek w `src/graphics/CMakeLists.txt` na odpowiadające instalacji dla odpowiedniego systemu operacyjnego

     ```cmake
       set(glad_DIR "<path_to_glad>")
       set(glm_DIR "<path_to_glm>")
       set(glfw3_DIR "<path_to_glfw>")
     ```

4. Wywołanie skryptu `build.sh` z repozytorium

   ```sh
     ./build.sh
   ```

5. Odpalenie programu

   ```sh
     ./build/release/src/game.exe [flagi]
   ```

   Gdzie do zadania opcji rozgrywki można wykorzystać flagi (_command line arguments_)

   - `--generator=<typ generatora>` | `--generator_type=<typ generatora>`
     > Typy generatorów:\
     > ALDOUS_BRODER | ELLERS | GROWING_TREE | HUNT_AND_KILL | KRUSKALS | PRIMS | RECURSIVE_BACKTRACKING | RECURSIVE_DIVISION | SIDEWINDER | WILSONS
   - `--solver=<typ solvera>` | `--solver_type=<typ solvera>`
     > Typy solverów:\
     > BREADTH_FIRST_SEARCH | A_STAR | DJIKSTRA
   - `--path=<typ ścieżki>` | `--path_type=<typ ścieżki>`
     > Typy ścieżek:\
     > BOTTOM_TO_TOP | BOTTOM_LEFT_TO_TOP_RIGHT | LEFT_TO_RIGHT | TOP_LEFT_TO_BOTTOM_RIGHT | TOP_TO_BOTTOM
   - `--difficulty=<poziom trudności>` | `--difficulty_level=<poziom trudności>`
     > Poziomy trudności:\
     > EASY | NORMAL | HARD
   - `--size={rows, cols}`

## Fakty dotyczące projektu
  - czas poświęcony na projekt:
    - frontend: 200h,
    - backend: 150h.
  
### Liczba linii kodu

> Wyznaczana za pomocą komendy _bash_

```sh
  find <dir> | grep '.*.cpp\|.*.hpp' | xargs wc -l
```
- Ilość linijek kodu: 5813

### Napotkane problemy
  -Bazując na nabytych doświadczeniach OpenGL nie stanowi zbyt przyjaznego środowiska dla początkujących. Aby zobaczyć pierwsze efekty przyswajania wiedzy dotyczącej graficznej biblioteki należało poświęcić wiele godzin.
  - Dużym błędem dotyczącym części graficznej projektu było tworzenie zbyt złożonych metod, co znacząco utrudniało testowanie poprawności działania oraz obniżyło czytelność kodu.
