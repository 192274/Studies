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

#ifndef SAPER_FIELD_H
#define SAPER_FIELD_H


class Field {

    bool mined;
    bool uncovered;
    bool flagged;

public:
    Field();

    void setMined(bool);
    void setUncovered(bool);
    void setFlagged(bool);

    bool hasMine() const;
    bool isUncovered() const;
    bool isFlagged() const;

    //display state of the field in the form [MUF], where M - is minned, U - is uncovered, F - is flagged and M,U,F belongs to {0,1}
    void info() const;
};


#endif //SAPER_FIELD_H
