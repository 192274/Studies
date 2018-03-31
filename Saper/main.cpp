#include <iostream>
#include <cstdlib>
#include <sstream>
#include "Field.h"
#include "Board.h"


std::string welcomeMessage{"Welcome to Saper game!\n\nTo release the field type its coordinates, for example 'a1'.\n"
                                   "To flag the field, type '?' and coordinates, like '?a1'. \n"
                                   "When you finish, press 'n' for new game and 'x' for exit.\n"
                                   "\n\nGood luck!\n\n "};

char charToX(char x);

void skipLine();

void makeMove(Board & board);

char getCommand();

Board setBoard() {
    int x, y, mines;
    std::cout << "X: \t";
    std::cin >> x;
    std::cout << "Y: \t";
    std::cin >> y;
    std::cout << "Mines: \t";
    std::cin >> mines;
    std::cout << "\n\n";    //when system("clear") doesn't work)
    system("clear");
    Board board(x, y);
    board.deployMines(mines);
    std::cin.ignore(100, '\n');
    return board;
}

int main() {
    system("clear");
    std::cout<<welcomeMessage;
    skipLine();
    while (true) {
        Board board = setBoard();
        do {
            board.display();
            makeMove(board);
            system("clear");
        } while(!board.isOver());
        board.finalDisplay();
        char command = getCommand();
        system("clear");
        if(command == 'x')
            return 0;
    }
}

char getCommand() {
    std::string line;
    char command = 0;
    while (command != 'n' && command != 'x') {
            getline(std::cin, line);
            std::stringstream lineStream(line);
            while(lineStream>>command && command != 'n'&& command != 'x') ;
        }
    return command;
}

void makeMove(Board &board) {
    std::cout << "\n>";
    char flag, x;
    int y = -1;
    std::string temp;
    getline(std::cin, temp);
    std::stringstream answer(temp);
    answer >> flag;
    if(flag == '?') {
        if(answer >> x >> y)
            board.setFlag(charToX(x), y);
    }
    else {
        answer.unget();
        if(answer >> x >> y) {
            board.reveal(charToX(x), y);
        }
    }
}

void skipLine() {
    std::__cxx11::string str;
    getline(std::cin, str);
}

char charToX(char x) {
    if(x >= 'a' && x <= 'z')
        x -= 'a';
    else
        x -= 'A';
    return x;
}

int boardTest() {
    Board board(3,8);
    board.deployMines(15, true);
    board.reveal(1, 0);
    board.setFlag(2, 5);
    board.display();
    board.debugDisplay();
    return 0;
}

int fieldTest() {
    Field f;
    f.setFlagged(true);
    f.setMined(true);
    f.info();
    return 0;
}
