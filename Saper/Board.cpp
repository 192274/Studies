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
reveal(x,y) - odkryj pole; jeśli na odkrytym polu jest mina, to w klasie plansza ustawiany jest znacznik sygnalizujący koniec gry*/

#include <iostream>
#include "Board.h"

//x, y check is left for Game class
Board::Board(const int x, const int y) : xSize(x), ySize(y) {
    fields.resize(x);
    for(int i = 0; i < x; ++i)
        fields[i].resize(y);
}

Board::Board() : xSize(20), ySize(10) {

}

void Board::deployMines(int amount, bool random) {
    if(random) {
        amount = properAmountOfMines(amount);
        deployMinesRandomly(amount);
    }
    else
    {
        deployMinesClassically();
    }
}

void Board::deployMinesClassically() {
    double yIncrease = (ySize - 1.) / (xSize - 1);
    double y = 0;
    for(int i = 0; i < xSize; ++i, y += yIncrease)
        {
            fields[i][y].setMined(true);
            fields[i][0].setMined(true);
        }
}

int Board::properAmountOfMines(int amount) const {
    if(amount <= 0)
            amount = 1;
        else {
            int maxMinesAmount = xSize * ySize - 1;
            if (amount > maxMinesAmount)
                amount = maxMinesAmount;
        }
    return amount;
}

void Board::deployMinesRandomly(int amount) {
    srand(time(0));
    while(amount)
        {
            Field & t {fields[rand() % xSize][rand() % ySize]};
            if(!t.hasMine())
            {
                t.setMined(true);
                amount--;
            }
        }
}

int Board::countMines(int x, int y) const {
    int result {0};

    for(int i = x - 1; i <= x + 1; ++i)
        for(int j = y - 1; j <= y + 1; ++j)
            result += hasMine(i, j);

    result -= hasMine(x, y);
    return result;
}

bool Board::hasMine(int x, int y) const {
    if(exists(x, y))
        return fields[x][y].hasMine();
    return false;
}

void Board::display() const {
    for(int y = 0; y < ySize; ++y) {
        for(int x = 0; x < xSize; ++x) {
            std::cout<</*'['<<*/symbol(x, y, 1);
        }
        std::cout<<std::endl;
    }
}

void Board::finalDisplay() const {
    for(int y = 0; y < ySize; y++) {
        for(int x = 0; x < xSize; x++)
            std::cout<<symbolEndGame(x, y);
        std::cout<<std::endl;
    }
}

void Board::debugDisplay() const {
    for(int i = 0; i < ySize; ++i) {
        for (int j = 0; j < xSize; ++j)
            fields[j][i].info();
        std::cout<<'\n';
    }
}

void Board::reveal(int x, int y) {
    if(exists(x, y)) {
        fields[x][y].setUncovered(true);
        if(!fields[x][y].hasMine() && countMines(x, y) == 0)
            for(int i = x - 1; i <= x + 1; i++)
                for(int j = y - 1; j <= y + 1; j++)
                    if(exists(i, j) && !fields[i][j].isUncovered())
                        reveal(i, j);
    }
}

char Board::symbol(int x, int y) const {
    if(fields[x][y].isUncovered())
    {
        if (hasMine(x, y))
            return 'x';
        else
        if (countMines(x, y) == 0)
            return ' ';
        else
            return countMines(x, y) + '0';
    }
    else
    {
        if (fields[x][y].isFlagged())
            return '?';
        else
            return '.';
    }
}

std::string Board::symbol(int x, int y, bool) const {
    char c = symbol(x, y);
    std::string s {"   "};
    if(c == '.')
    {
        s[0] = x + 65;
        int i = s.size() - 1;
        do
        {
            s[i] = y % 10 + 48;
            y /= 10;
        } while(i-- > 0 && y);
        return blackStyleBegin + s + styleEnd;
    }
    s[1] = c;
    if(c == 'x')
        return redStyleBegin + s + styleEnd;
    return whiteStyleBegin + s + styleEnd;
}

std::string Board::symbolEndGame(int x, int y) const {
    char c;
    if (hasMine(x, y))
        c = 'x';
    else
        if (countMines(x, y) == 0)
            c = ' ';
        else
            c = countMines(x, y) + '0';
    if(fields[x][y].isUncovered())
        if(fields[x][y].hasMine())
            return redStyleBegin + " " + c + " " + styleEnd;
        else
            return whiteStyleBegin + " " + c + " " + styleEnd;
    else
        if(fields[x][y].hasMine())
            return reverseRedStyleBegin + " " + c + " " + styleEnd;
        else
            return blackStyleBegin+ " " + c + " " + styleEnd;
}

void Board::setFlag(int x, int y) {
    if(exists(x, y))
        fields[x][y].setFlagged(true);
}

bool Board::isOver() {
    if(revealedMine()) {
        std::cout<<"\nY O U  L O O S E !\n\n";
        return true;
    }
    if(hasCoveredUnminedField()) {
        return false;
    }
    std::cout<<"\nC O N G R A T U L A T I O N S,  Y O U  W I N !\n\n";
    return true;
}

bool Board::revealedMine() const {
    for(auto fieldsVector : fields)
        for(auto field : fieldsVector)
            if(field.hasMine() && field.isUncovered())
                return true;
    return false;
}

bool Board::hasCoveredUnminedField() const {
    for(auto fieldsVector : fields)
        for(auto field : fieldsVector)
            if(!field.hasMine() && !field.isUncovered()) {
                return true;
            }
    return false;
}

bool Board::exists(int x, int y) const {
    if(x < 0 || x >= xSize || y < 0 || y >= ySize)
        return false;
    return true;
}

