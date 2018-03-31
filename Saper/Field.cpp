//
// Created by w on 3/8/18.
//

/*Klasa reprezentująca jedno pole w grze Saper.

Każde pole ma swój stan:

czy posiada minę ?
czy zostało odkryte ?
czy zostało oznaczone flagą ?
W klasie proszę stworzyć

konstruktor ustawiający parametry domyślne pola (brak miny, ukryte, brak flagi)
funkcje pozwalające modyfikować i odczytywać stan pola
pomocniczą funkcję info() wyświetlającą stan pola w postaci trzech liczb lub znaczników np. [010] (nie ma miny, odkryte, nie ma flagi)*/

#include <iostream>
#include "Field.h"

Field::Field() : mined(false), uncovered(false), flagged(false) {

}

void Field::setMined(bool isMined) {
    mined = isMined;
}

void Field::setUncovered(bool isUncovered) {
    uncovered = isUncovered;
}

void Field::setFlagged(bool isFlagged) {
    flagged = isFlagged;
}

bool Field::hasMine() const {
    return mined;
}

bool Field::isUncovered() const {
    return uncovered;
}

bool Field::isFlagged() const {
    return flagged;
}

void Field::info() const {
    std::cout<<'['<< hasMine()<< isUncovered()<< isFlagged()<<']';
}

