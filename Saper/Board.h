//
// Created by w on 3/8/18.
//

/*Klasa reprezentująca całą planszę

Plansza jest prostokątnym obszarem o wymiarach M*N. Każdy "element" tego obszaru to zdefiniowane wcześniej "pole".

W klasie reprezentującej planszę należy stworzyć następujące funkcje

konstruktor określający rozmiar planszy
funkcja deployMines(int n, bool randrom) - ustawia na planszy n min
w losowych pozycjach jeśli parametr random ma wartość true
w pierwszym wierszu i na przekątnej jeśli parametr random ma wartość false (w tym przypadku wartość n jest ignorowana)
debug_display() - pomocnicza funkcja wyświetlająca całą planszę (wywołuje funkcję info() dla każdego pola planszy)
hasMine(int x, int y) - zwraca prawdę, jeśli na polu jest mina. Zwraca fałsz jeśli na polu nie ma miny albo jeśli podane współrzędne leżą poza planszą
countMines(intx, int y) - funkcja liczy ile jest min w otoczeniu pola o współrzędnych x,y (wskazówka - użyj zdefiniowanej wcześniej funkcji hasMine() )
display() - wyświetla planszę zgodnie z regułami gry, czyli
[.] - jeśli pole jest zakryte i nie jest oznaczone flagą
[?] - jeśli pole jest zakryte i jest oznaczone flagą
[ ] - jeśli pole jest odkryte, nie ma na nim miny i w sąsiedztwie jest 0 min
[3] - j.w., ale w otoczeniu pola są 3 miny
[x] - na odkrytym polu jest mina (koniec gry !)
reveal(x,y) - odkryj pole; jeśli na odkrytym polu jest mina, to w klasie plansza ustawiany jest znacznik sygnalizujący koniec gry

 // funkcja liczy ile jest min w otoczeniu pola o współrzędnych (x,y)
int licz_miny(int x, int y);

UWAGA: sugestia - dodaj funkcję pomocniczą
int czy_jest_mina(int x, int y);
Ta funkcja sprawdza czy x i y są prawidłowe (tzn czy sprawdzamy pole na planszy) i jeśli nie - zwraca zero. Jeśli x i y są poprawne, funkcja zwraca 1 jeśli na polu jest mina, zero jeśli jej nie ma.

// funkcja "odkrywa" pole.
void odkryj(int x, int y);

// funkcja "ustawia" flagę
void ustaw_flage(int x, int y);

// funkcja sprawdza czy (kiedykolwiek) odkryto pole zawierające minę - jeśli tak zwraca prawdę
bool czy_gra_skonczona();
// funkcja zwraca symbol reprezentujący zawartość pola o współrzędnych (x,y)
// Funkcja może zwrócić następujące symbole:
// _ (podkreślenie) - pole jest zakryte i nie posiada ustawionej flagi
// F (litera F) - pole jest zakryte i posiada ustawioną flagę
// " " (spacja) - pole jest odkryte, nie ma na nim miny i w jego otoczeniu nie ma żadnej miny
// 1...8 - pole jest odkryte, nie ma na nim miny i w jego otoczeniu jest od 1 do 8 min
// x (litera x) - pole jest odkryte i zawieta minę
char zawartosc_pola(int x, int y);*/

#ifndef SAPER_BOARD_H
#define SAPER_BOARD_H

#include <vector>
#include <string>
#include <cstdlib>
#include "Field.h"




static const std::string blackStyleBegin = "\033[7;30m["; //EXTRA

static const std::string styleEnd = "]\033[0m"; //EXTRA

static const std::string whiteStyleBegin = "\033[1;30m["; //EXTRA

static  const std::string redStyleBegin = "\033[1;35m["; //EXTRA

static const std::string reverseRedStyleBegin = "\033[40;35m["; //EXTRA


class Board {

public:
    Board();
    Board(int x = 60, int y = 40);

    //deployMines(int, bool) returns false if 'amount' was too less or too large and then set minimum or maximum of allowed mines
    void deployMines(int amount, bool random = true);

    //debugDisplay() displays fields in the form [Minned Uncovered Flagged] for each field
    void debugDisplay() const;

    //display() displays fields in the form: [.] covered, [?] flagged, [ ] uncovered with 0 contiguos mines,
    //[3] uncovered with 3 contiguos mines, [x] uncovered with mine
    void display() const;

    void reveal(int x, int y);

    void setFlag(int x, int y);

    bool isOver();

    //displays all fields information - if has mine or amount of mines in neightbourhood
    void finalDisplay() const; //EXTRA

    class invalidConstructorParams{};

private:

    const int xSize;
    const int ySize;
    std::vector<std::vector<Field> > fields;

    bool hasMine(int x, int y) const;

    char symbol(int x, int y) const;

    std::string symbol(int x, int y, bool) const; //EXTRA

    bool exists(int x, int y) const; //EXTRA but used in hasMine

    bool revealedMine() const; //EXTRA but used in isOver

    //return sum of mines in contiguos fields
    int countMines(int x, int y) const;

    void deployMinesRandomly(int amount); //EXTRA but used in deployMines

    int properAmountOfMines(int amount) const; //EXTRA but used for deployMines

    void deployMinesClassically(); //EXTRA but used in deployMines

    bool hasCoveredUnminedField() const; //EXTRA but used for isOver

    std::string symbolEndGame(int x, int y) const; //EXTRA
};


#endif //SAPER_BOARD_H
